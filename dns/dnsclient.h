
#ifndef DNSCLIENT_H
#define DNSCLIENT_H


#include <QObject>
#include <QUdpSocket>

#include "dns.h"
#include <vector>


class DnsClient : public QObject
{
    Q_OBJECT
public:
    explicit DnsClient(QObject* parent = nullptr);
    ~DnsClient();
    bool encodeDotStr(char* szDotStr, char* szEncodedStr, USHORT nEncodedStrSize);
    bool sendRequest(QString ip, QString doMainName);


public slots:
    void onReadyRead();


signals:
private:
    QUdpSocket* m_socket;
    USHORT m_currentProcID;
    char* m_szDNSPacket;

};

#endif // DNSCLIENT_H
