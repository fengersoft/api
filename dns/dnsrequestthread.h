
#ifndef DNSREQUESTTHREAD_H
#define DNSREQUESTTHREAD_H


#include <QObject>
#include <QThread>
#include <QUdpSocket>
#include "dnsrequest.h"


class DnsRequestThread : public QThread
{
    Q_OBJECT
public:
    explicit DnsRequestThread(QObject* parent = nullptr);

    QUdpSocket* server() const;
    void setServer(QUdpSocket* newServer);

    QHostAddress address() const;
    void setAddress(const QHostAddress& newAddress);

    quint16 port() const;
    void setPort(quint16 newPort);

    QByteArray data() const;
    void setData(const QByteArray& newData);

    QUdpSocket *client() const;
    void setClient(QUdpSocket *newClient);

signals:
public slots:
    void onReadyRead();
protected:
    void run();
private:
    QUdpSocket* m_server;
    QUdpSocket* m_client;
    QHostAddress m_address;
    quint16 m_port;
    QByteArray m_data;

};

#endif // DNSREQUESTTHREAD_H
