#include "localip.h"
QSharedPointer<LocalIp> LocalIp::m_localIp = nullptr;
LocalIp::LocalIp(QObject* parent)
    : QObject{parent}
{
    QList<QHostAddress> addrsses = QNetworkInterface::allAddresses();
    QStringList stl;
    for (const QHostAddress& address : addrsses)
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            QString info = address.toString();
            if (info.startsWith("169"))
            {
                continue;
            }
            else if (info.endsWith(".1"))
            {
                continue;
            }
            else if (info.endsWith(".255"))
            {
                continue;
            }
            stl << info;
        }

    }
    m_ips = stl.join(",");

}

LocalIp* LocalIp::instance()
{
    if (LocalIp::m_localIp == nullptr)
    {
        m_localIp = QSharedPointer<LocalIp>(new LocalIp());
    }
    return m_localIp.get();

}

QString LocalIp::ips() const
{
    return m_ips;
}

void LocalIp::setIps(const QString& newIps)
{
    m_ips = newIps;
}

LocalIp* localIp()
{
    return LocalIp::instance();

}
