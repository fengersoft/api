
#ifndef DNSSERVER_H
#define DNSSERVER_H


#include <QObject>
#include <QUdpSocket>
#include <QEventLoop>
#include <QNetworkDatagram>
#include <QDateTime>
#include <QTimer>
#include <thread>

#include "dnsrequest.h"
#include "dnsrequestthread.h"


class DnsServer : public QObject
{
    Q_OBJECT
public:
    explicit DnsServer(QObject* parent = nullptr);

signals:
public slots:
    void onReadyRead();
private:
    QUdpSocket* m_server;

};

#endif // DNSSERVER_H
