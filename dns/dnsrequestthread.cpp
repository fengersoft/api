
#include "dnsrequestthread.h"

DnsRequestThread::DnsRequestThread(QObject* parent)
    : QThread{parent}
{

}

void DnsRequestThread::run()
{

    qDebug() << "run";



    connect(m_client, &QUdpSocket::readyRead, this, &DnsRequestThread::onReadyRead, Qt::QueuedConnection);

    m_client->writeDatagram(m_data, QHostAddress("8.8.8.8"), 53);
    qDebug() << "send";
    exec();


}

QByteArray DnsRequestThread::data() const
{
    return m_data;
}

void DnsRequestThread::setData(const QByteArray& newData)
{
    m_data = newData;
}

void DnsRequestThread::onReadyRead()
{
    qDebug() << m_data;
    // DnsRequest* request = new DnsRequest();
    //request->setSrcData(m_data);
    QUdpSocket* send = static_cast<QUdpSocket*>(sender());


    qDebug() << "start";
    while (send->hasPendingDatagrams())
    {
        QByteArray allData;
        allData.resize(send->pendingDatagramSize());

        send->readDatagram(allData.data(), allData.size());
        m_server->writeDatagram(allData.data(), allData.size(),
                                m_address, m_port);

    }
    send->disconnectFromHost();
    delete send;
    //delete request;

}

quint16 DnsRequestThread::port() const
{
    return m_port;
}

void DnsRequestThread::setPort(quint16 newPort)
{
    m_port = newPort;
}

QHostAddress DnsRequestThread::address() const
{
    return m_address;
}

void DnsRequestThread::setAddress(const QHostAddress& newAddress)
{
    m_address = newAddress;
}

QUdpSocket* DnsRequestThread::server() const
{
    return m_server;
}

void DnsRequestThread::setServer(QUdpSocket* newServer)
{
    m_server = newServer;
}


QUdpSocket *DnsRequestThread::client() const
{
    return m_client;
}

void DnsRequestThread::setClient(QUdpSocket *newClient)
{
    m_client = newClient;
}
