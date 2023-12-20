
#ifndef DNSREQUEST_H
#define DNSREQUEST_H


#include <QObject>
#include <QDebug>
#include "dns.h"


class DnsRequest : public QObject
{
    Q_OBJECT
public:
    explicit DnsRequest(QObject* parent = nullptr);
    ~DnsRequest();

    QByteArray srcData() const;
    void setSrcData(const QByteArray& newSrcData);

    QString cname() const;
    void setCname(const QString &newCname);

signals:
private:
    QByteArray m_srcData;
    DNSQuestion* m_question;
    QString m_cname;

};

#endif // DNSREQUEST_H
