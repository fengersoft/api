
#include "dnsrequest.h"


DnsRequest::DnsRequest(QObject* parent)
    : QObject{parent}
{
    m_question = new DNSQuestion();

}

DnsRequest::~DnsRequest()
{
    delete m_question;

}

QByteArray DnsRequest::srcData() const
{
    return m_srcData;
}

void DnsRequest::setSrcData(const QByteArray& newSrcData)
{
    m_srcData = newSrcData;
    char* data = m_srcData.data();
    int n = m_srcData.length() - sizeof(DNSHeader) - 2;

    if (n < 0)
    {
        return;
    }
    char* enCname = new char[n];
    memset(enCname, 0, n);
    memcpy(enCname, data + sizeof(DNSHeader), n);
    char cname[1024] = {'\0'};
    USHORT ns = n;
    decodeDotStr(enCname, &ns, cname, sizeof(cname), 0);
    m_cname = QString::fromLocal8Bit(cname);


    delete[] enCname;

}

QString DnsRequest::cname() const
{
    return m_cname;
}

void DnsRequest::setCname(const QString &newCname)
{
    m_cname = newCname;
}

