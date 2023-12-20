
#ifndef DNS_H
#define DNS_H
#include <winsock2.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

/* flags */
#define DNS_QUERY (0 << 15) /* 0 = query; 1 = response */
#define DNS_RESPONSE (1 << 15)
#define DNS_STDQUERY (0) /* opcode - 4 bits */
#define DNS_INVQUERY (1 << 11)
#define DNS_SRVSTATUS (1 << 12)
#define DNS_AA (1 << 10) /* authoritative answer */
#define DNS_TC (1 << 9) /* truncated */
#define DNS_RD (1 << 8) /* recursion desired */
#define DNS_RA (1 << 7) /* recursion available */

/* query classes */
#define DNS_INET 1

/* DNS query types */
#define DNS_A 1 /* name -> IP */
#define DNS_NS 2 /* name server */
#define DNS_CNAME 5 /* canonical name */
#define DNS_PTR 12 /* IP->name */
#define DNS_HINFO 13 /* host info/SOA */
#define DNS_MX 15 /* mail exchange */
#define DNS_AXFR 252 /* request for zone transfer */
#define DNS_ANY 255 /* all records */


#define DNS_OK 0 /* rcode = reply codes */
#define DNS_FORMAT 1 /* format error (unable to interpret) */
#define DNS_SERVERFAIL 2 /* server failure */
#define DNS_ERROR 3 /* no DNS entry */
#define DNS_NOTIMPL 4 /* not implemented */
#define DNS_REFUSED 5 /* server refused the query */

#define RCODE_MASK 0xF

#define BIT(x) (1 << x)
#define COMPRESSION_MASK (~(BIT(15)|BIT(14)))


#define MAX_DOMAINNAME_LEN  255
#define DNS_PORT            53
#define DNS_TYPE_SIZE       2
#define DNS_CLASS_SIZE      2
#define DNS_TTL_SIZE        4
#define DNS_DATALEN_SIZE    2
#define DNS_TYPE_A          0x0001 //1 a host address
#define DNS_TYPE_CNAME      0x0005 //5 the canonical name for an alias
#define DNS_PACKET_MAX_SIZE (sizeof(DNSHeader) + MAX_DOMAINNAME_LEN + DNS_TYPE_SIZE + DNS_CLASS_SIZE)

struct DNSHeader
{
    USHORT usTransID; //标识符
    USHORT usFlags; //各种标志位
    USHORT usQuestionCount; //Question字段个数
    USHORT usAnswerCount; //Answer字段个数
    USHORT usAuthorityCount; //Authority字段个数
    USHORT usAdditionalCount; //Additional字段个数
};
struct DNSQuestion
{
    int length;
    unsigned short qtype;
    unsigned short qclass;
    char* name;//域名
};
int createDnsHeader(DNSHeader* header);
int createDnsQuestion(DNSQuestion* question, const char* hostname);
int dnsBuildRequestion(DNSHeader* header, DNSQuestion* question, char* request, int rlen);
bool decodeDotStr(char* szEncodedStr, USHORT* pusEncodedStrLen,
                  char* szDotStr, USHORT nDotStrSize, char* szPacketStartPos);

#endif // DNS_H
