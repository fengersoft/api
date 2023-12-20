#include "dns.h"

int createDnsHeader(DNSHeader* header)
{
    if (header == nullptr)
        return -1;
    memset(header, 0, sizeof(DNSHeader));

    //random
    srand(time(NULL));//设置种子(因为种子根据时间有关，每次random也会变，因此这是一个线程不安全的)
    header->usTransID = rand(); //获得随机数

    header->usFlags = htons(0x0100); //转化为网络字节序
    header->usQuestionCount = htons(1); //每次查询一个域名
    return 0;
}
//创建question
//hostname:www.baidu.com
//name:3www5baidu3com'\0'
int createDnsQuestion(DNSQuestion* question, const char* hostname)
{
    if (question == NULL || hostname == NULL)
        return -1;
    memset(question, 0, sizeof(DNSQuestion));
    question->name = (char*)malloc(strlen(hostname) + 2); //因为要判断结尾'\0'，然后再补充一个开头3
    if (question->name == NULL) //如果内存分配失败
    {
        return -2;
    }
    question->length = strlen(hostname) + 2;
    question->qtype = htons(1); //查询类型，（1表示：由域名获得 IPv4 地址）
    question->qclass = htons(1); //通常为 1，表明是 Internet 数据

    //hostname->name
    const char delim[2] = "."; //分隔符,末尾补个'\0'
    char* qname = question->name;
    char* hostname_dup = strdup(hostname); //复制一份hostname  --->malloc(所以后续要free)
    char* token = strtok(hostname_dup, delim);
    while (token != NULL)
    {
        size_t len = strlen(token); //第一个循环token为www,len=3
        *qname = len; //先把长度放上去
        qname++;
        strncpy(qname, token, len + 1); //复制www，这里不+1也是可以的，这样是为了把最后的'\0'也复制过来,因为最后也会被覆盖的。(如果这边不+1，最后一步，需要额外加上'\0')
        qname += len;
        token = strtok(NULL, delim); //因为上一次，token获取还未结束，因此可以指定NULL即可。(注意：要依赖上一次的结果，因此也是线程不安全的)
    }
    free(hostname_dup);
    return 0;
}

//struct dns_header* header
//struct dns_question* question
//把上面两个合到request中 返回长度
int dnsBuildRequestion(DNSHeader* header, DNSQuestion* question, char* request, int rlen)
{
    if (header == NULL || question == NULL || request == NULL)
        return -1;
    memset(request, 0, rlen);

    //header-->request
    memcpy(request, header, sizeof(DNSHeader)); //把header的数据 拷贝 到request中
    int offset = sizeof(DNSHeader);

    //question-->request
    memcpy(request + offset, question->name, question->length);
    offset += question->length;
    memcpy(request + offset, &question->qtype, sizeof(question->qtype));
    offset += sizeof(question->qtype);
    memcpy(request + offset, &question->qclass, sizeof(question->qclass));
    offset += sizeof(question->qclass);
    return offset;
}
/*
 * convert "\x03www\x05baidu\x03com\x00" to "www.baidu.com"
 * 0x0000 03 77 77 77 05 62 61 69 64 75 03 63 6f 6d 00 ff
 * convert "\x03www\x05baidu\xc0\x13" to "www.baidu.com"
 * 0x0000 03 77 77 77 05 62 61 69 64 75 c0 13 ff ff ff ff
 * 0x0010 ff ff ff 03 63 6f 6d 00 ff ff ff ff ff ff ff ff
 */
bool decodeDotStr(char* szEncodedStr, USHORT* pusEncodedStrLen, char* szDotStr, USHORT nDotStrSize, char* szPacketStartPos)
{
    if (szEncodedStr == NULL || pusEncodedStrLen == NULL || szDotStr == NULL)
    {
        return FALSE;
    }

    char* pDecodePos = szEncodedStr;
    USHORT usPlainStrLen = 0;
    BYTE nLabelDataLen = 0;
    *pusEncodedStrLen = 0;

    while ((nLabelDataLen = *pDecodePos) != 0x00)
    {
        if ((nLabelDataLen & 0xc0) == 0) //普通格式，LabelDataLen + Label
        {
            if (usPlainStrLen + nLabelDataLen + 1 > nDotStrSize)
            {
                return false;
            }
            memcpy(szDotStr + usPlainStrLen, pDecodePos + 1, nLabelDataLen);
            memcpy(szDotStr + usPlainStrLen + nLabelDataLen, ".", 1);
            pDecodePos += (nLabelDataLen + 1);
            usPlainStrLen += (nLabelDataLen + 1);
            *pusEncodedStrLen += (nLabelDataLen + 1);
        }
        else //消息压缩格式，11000000 00000000，两个字节，前2位为跳转标志，后14位为跳转的偏移
        {
            if (szPacketStartPos == NULL)
            {
                return FALSE;
            }
            USHORT usJumpPos = ntohs(*(USHORT*)(pDecodePos)) & 0x3fff;
            USHORT nEncodeStrLen = 0;
            if (!decodeDotStr(szPacketStartPos + usJumpPos, &nEncodeStrLen, szDotStr + usPlainStrLen, nDotStrSize - usPlainStrLen, szPacketStartPos))
            {
                return false;
            }
            else
            {
                *pusEncodedStrLen += 2;
                return true;
            }
        }
    }

    szDotStr[usPlainStrLen - 1] = '\0';
    *pusEncodedStrLen += 1;

    return true;
}
