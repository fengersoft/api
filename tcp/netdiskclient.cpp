#include "netdiskclient.h"

NetDiskClient::NetDiskClient(QObject* parent)
    : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_ip = "127.0.0.1";
    m_port = 9001;
}

QString NetDiskClient::ip() const
{
    return m_ip;
}

void NetDiskClient::setIp(const QString& ip)
{
    m_ip = ip;
}

int NetDiskClient::port() const
{
    return m_port;
}

void NetDiskClient::setPort(int port)
{
    m_port = port;
}

bool NetDiskClient::connectHost()
{
    m_socket->connectToHost(m_ip, m_port);
    m_isConnected = m_socket->isOpen();
    return m_isConnected;
}

bool NetDiskClient::isConnected() const
{
    return m_isConnected;
}

void NetDiskClient::setIsConnected(bool isConnected)
{
    m_isConnected = isConnected;
}

void NetDiskClient::uploadFile(QString filename)
{
    qDebug() << filename;
    QCryptographicHash md5(QCryptographicHash::Md5);
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    md5.addData(data);
    QString md5str = md5.result().toHex().toLower();
    if (!m_socket->isOpen())
    {
        m_socket->connectToHost(m_ip, m_port);
    }

    QString cmd = "upload\n";
    QByteArray cmdData;
    cmdData.append(cmd);
    m_socket->write(cmdData);
    m_socket->write(data);
    while (m_socket->waitForBytesWritten())
    {
        QApplication::processEvents();
    }
}

void NetDiskClient::uploadFile(QString filename, QString md5)
{
    qDebug() << filename;

    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    if (!m_socket->isOpen())
    {
        m_socket->connectToHost(m_ip, m_port);
    }

    QString cmd = "upload\n";
    QByteArray cmdData;
    cmdData.append(cmd);
    m_socket->write(cmdData);
    m_socket->write(data);
}

void NetDiskClient::downloadFileByMd5(QString md5, QString fileName)
{
    if (!m_socket->isOpen())
    {
        m_socket->connectToHost(m_ip, m_port);
    }

    QString cmd = "download\n";
    QByteArray cmdData;
    cmdData.append(cmd);
    m_socket->write(cmdData);
    cmdData.clear();
    cmdData.append(md5 + "\n");
    m_socket->write(cmdData);
    QByteArray data;
    while (m_socket->waitForReadyRead(10))
    {
        data.append(m_socket->readAll());
    }
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.flush();
    file.close();
}
