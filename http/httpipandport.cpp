#include "httpipandport.h"

HttpIpAndPort::HttpIpAndPort(QObject* parent)
    : QObject{parent}
{

}

const QString& HttpIpAndPort::ipAndPort() const
{
    return m_ipAndPort;
}

void HttpIpAndPort::setIpAndPort(const QString& newIpAndPort)
{
    m_ipAndPort = newIpAndPort;
}

QString HttpIpAndPort::ip()
{
    int m = m_ipAndPort.indexOf("//");
    int n = m_ipAndPort.lastIndexOf(":");
    QString sip = m_ipAndPort.mid(m + 2, n - m - 2);
    return sip;

}

QString HttpIpAndPort::port()
{
    int n = m_ipAndPort.lastIndexOf(":");
    QString sPort = m_ipAndPort.mid(n + 1);
    return sPort;
}
