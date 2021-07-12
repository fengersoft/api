#ifndef NETDISKCLIENT_H
#define NETDISKCLIENT_H

#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QObject>
#include <QTcpSocket>
#include <QNetworkConfigurationManager>
#include <QApplication>

class NetDiskClient : public QObject
{
    Q_OBJECT
public:
    explicit NetDiskClient(QObject* parent = nullptr);

    QString ip() const;
    void setIp(const QString& ip);

    int port() const;
    void setPort(const int port);
    bool connectHost();

    bool isConnected() const;
    void setIsConnected(bool isConnected);
    void uploadFile(QString filename);
    void uploadFile(QString filename, QString md5);
    void downloadFileByMd5(QString md5, QString fileName);

signals:

private:
    QString m_ip;
    int m_port;
    QTcpSocket* m_socket;
    bool m_isConnected;
};

#endif // NETDISKCLIENT_H
