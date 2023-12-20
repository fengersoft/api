
#include "dnsserver.h"


DnsServer::DnsServer(QObject* parent)
    : QObject{parent}
{
    m_server = new QUdpSocket(this);
    m_server->bind(53);

    connect(m_server, &QUdpSocket::readyRead, this, &DnsServer::onReadyRead);

}

void DnsServer::onReadyRead()
{
    qDebug() << "onReadyRead";
    QUdpSocket* socket = static_cast<QUdpSocket*>(sender());
    while (socket->hasPendingDatagrams())
    {
        QByteArray data;
        QHostAddress addr;
        quint16 port;
        data.resize(socket->pendingDatagramSize());
        socket->readDatagram(data.data(), data.size(), &addr, &port);
        QThread* t = QThread::create([this](QHostAddress addr, quint16 port, QByteArray  data)
        {

            DnsRequest* request = new DnsRequest();
            request->setSrcData(data);
            qDebug() << request->cname();
            QUdpSocket* client = new QUdpSocket();
            client->writeDatagram(data, QHostAddress("8.8.8.8"), 53);
            QEventLoop loop;
            connect(client, &QUdpSocket::readyRead, &loop, &QEventLoop::quit);
            loop.exec();

            while (client->hasPendingDatagrams())
            {
                QByteArray allData;
                allData.resize(client->pendingDatagramSize());

                client->readDatagram(allData.data(), allData.size());
                m_server->writeDatagram(allData.data(), allData.size(),
                                        addr, port);
                qDebug() << "getData"  << QDateTime::currentDateTime() << allData.size();


            }
            client->disconnectFromHost();


            delete client;
            delete request;

        }, addr, port, data);
        connect(t, &QThread::finished, t, &QObject::deleteLater);//线程结束释放工作类
        t->start();







    }

}

