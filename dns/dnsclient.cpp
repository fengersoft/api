
#include "dnsclient.h"

DnsClient::DnsClient(QObject* parent)
    : QObject{parent}
{
    m_socket = new QUdpSocket(this);
    connect(m_socket, &QUdpSocket::readyRead, this, &DnsClient::onReadyRead);
    m_currentProcID = USHORT(GetCurrentProcessId());
    m_szDNSPacket = new (std::nothrow) char[DNS_PACKET_MAX_SIZE];

}

DnsClient::~DnsClient()
{
    if (m_szDNSPacket != NULL)
    {
        delete [] m_szDNSPacket;
    }

}

bool DnsClient::sendRequest(QString ip, QString doMainName)
{
    char* pWriteDNSPacket = m_szDNSPacket;
    memset(pWriteDNSPacket, 0, DNS_PACKET_MAX_SIZE);

    //填充DNS查询报文头部
    DNSHeader* pDNSHeader = (DNSHeader*)pWriteDNSPacket;
    pDNSHeader->usTransID = m_currentProcID;
    pDNSHeader->usFlags = htons(0x0100);
    pDNSHeader->usQuestionCount = htons(0x0001);
    pDNSHeader->usAnswerCount = 0x0000;
    pDNSHeader->usAuthorityCount = 0x0000;
    pDNSHeader->usAdditionalCount = 0x0000;

    //设置DNS查询报文内容
    USHORT usQType = htons(0x0001);
    USHORT usQClass = htons(0x0001);
    char* szDomainName = doMainName.toLocal8Bit().data();
    USHORT nDomainNameLen = strlen(szDomainName);
    char* szEncodedDomainName = (char*)malloc(nDomainNameLen + 2);
    if (szEncodedDomainName == NULL)
    {
        return false;
    }
    if (!encodeDotStr(szDomainName, szEncodedDomainName, nDomainNameLen + 2))
    {
        return false;
    }

    //填充DNS查询报文内容
    USHORT nEncodedDomainNameLen = strlen(szEncodedDomainName) + 1;
    memcpy(pWriteDNSPacket += sizeof(DNSHeader), szEncodedDomainName, nEncodedDomainNameLen);
    memcpy(pWriteDNSPacket += nEncodedDomainNameLen, (char*)(&usQType), DNS_TYPE_SIZE);
    memcpy(pWriteDNSPacket += DNS_TYPE_SIZE, (char*)(&usQClass), DNS_CLASS_SIZE);
    free(szEncodedDomainName);

    //发送DNS查询报文
    USHORT nDNSPacketSize = sizeof(DNSHeader) + nEncodedDomainNameLen + DNS_TYPE_SIZE + DNS_CLASS_SIZE;

    m_socket->writeDatagram(m_szDNSPacket, nDNSPacketSize, QHostAddress(ip), 53);

    return true;



}

void DnsClient::onReadyRead()
{

    while (m_socket->hasPendingDatagrams())
    {
        std::vector<ULONG>* pveculIPList = new std::vector<ULONG>();
        std::vector<std::string>* pvecstrCNameList = new std::vector<std::string>();
        int size = m_socket->pendingDatagramSize();
        char szDotName[128] = {'\0'};
        USHORT nEncodedNameLen = 0;
        qDebug() << size;
        char* recvbuf = new char[size];
        m_socket->readDatagram(recvbuf, size);
        DNSHeader* pDNSHeader = (DNSHeader*)recvbuf;
        USHORT usQuestionCount = 0;
        USHORT usAnswerCount = 0;
        if (pDNSHeader->usTransID == m_currentProcID
            && (ntohs(pDNSHeader->usFlags) & 0xfb7f) == 0x8100 //RFC1035 4.1.1(Header section format)
            && (usQuestionCount = ntohs(pDNSHeader->usQuestionCount)) >= 0
            && (usAnswerCount = ntohs(pDNSHeader->usAnswerCount)) > 0)
        {
            char* pDNSData = recvbuf + sizeof(DNSHeader);

            //解析Question字段
            for (int q = 0; q != usQuestionCount; ++q)
            {
                if (!decodeDotStr(pDNSData, &nEncodedNameLen, szDotName, sizeof(szDotName), 0))
                {
                    return;
                }
                pDNSData += (nEncodedNameLen + DNS_TYPE_SIZE + DNS_CLASS_SIZE);
            }

            //解析Answer字段
            for (int a = 0; a != usAnswerCount; ++a)
            {
                if (!decodeDotStr(pDNSData, &nEncodedNameLen, szDotName, sizeof(szDotName), recvbuf))
                {
                    return;
                }
                pDNSData += nEncodedNameLen;

                USHORT usAnswerType = ntohs(*(USHORT*)(pDNSData));
                USHORT usAnswerClass = ntohs(*(USHORT*)(pDNSData + DNS_TYPE_SIZE));
                ULONG usAnswerTTL = ntohl(*(ULONG*)(pDNSData + DNS_TYPE_SIZE + DNS_CLASS_SIZE));
                USHORT usAnswerDataLen = ntohs(*(USHORT*)(pDNSData + DNS_TYPE_SIZE + DNS_CLASS_SIZE + DNS_TTL_SIZE));
                pDNSData += (DNS_TYPE_SIZE + DNS_CLASS_SIZE + DNS_TTL_SIZE + DNS_DATALEN_SIZE);

                if (usAnswerType == DNS_TYPE_A && pveculIPList != NULL)
                {
                    ULONG ulIP = *(ULONG*)(pDNSData);
                    pveculIPList->push_back(ulIP);
                }
                else if (usAnswerType == DNS_TYPE_CNAME && pvecstrCNameList != NULL)
                {
                    if (!decodeDotStr(pDNSData, &nEncodedNameLen, szDotName, sizeof(szDotName), recvbuf))
                    {
                        return;
                    }
                    pvecstrCNameList->push_back(szDotName);
                }

                pDNSData += (usAnswerDataLen);
            }
            for (int i = 0; i < pvecstrCNameList->size(); i++)
            {
                qDebug() << pvecstrCNameList->at(i);
            }
            for (qsizetype  i = 0; i < pveculIPList->size(); i++)
            {
                uchar* ip = (uchar*)& pveculIPList->at(i);
                qDebug() << ip[0] << ip[1] << ip[2] << ip[3];
            }
        }


    }
}

bool DnsClient::encodeDotStr(char* szDotStr, char* szEncodedStr, USHORT nEncodedStrSize)
{
    USHORT nDotStrLen = strlen(szDotStr);

    if (szDotStr == NULL || szEncodedStr == NULL || nEncodedStrSize < nDotStrLen + 2)
    {
        return FALSE;
    }

    char* szDotStrCopy = new char[nDotStrLen + 1];
    //strcpy_s(szDotStrCopy, nDotStrLen + 1, szDotStr);
    strcpy(szDotStrCopy, szDotStr);

    char* pNextToken = NULL;
    //char *pLabel = strtok_s(szDotStrCopy, ".", &pNextToken);
    char* pLabel = strtok(szDotStrCopy, ".");
    USHORT nLabelLen = 0;
    USHORT nEncodedStrLen = 0;
    while (pLabel != NULL)
    {
        if ((nLabelLen = strlen(pLabel)) != 0)
        {
            //sprintf_s(szEncodedStr + nEncodedStrLen, nEncodedStrSize - nEncodedStrLen, "%c%s", nLabelLen, pLabel);
            sprintf(szEncodedStr + nEncodedStrLen, "%c%s", nLabelLen, pLabel);
            nEncodedStrLen += (nLabelLen + 1);
        }
        //pLabel = strtok_s(NULL, ".", &pNextToken);
        pLabel = strtok(NULL, ".");
    }

    delete [] szDotStrCopy;

    return TRUE;
}



