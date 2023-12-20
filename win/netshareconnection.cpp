#include "netshareconnection.h"
#include <winerror.h>
#include <winnetwk.h>
#include <winsock2.h>
#include <windows.h>
#include "windef.h"
NetShareConnection::NetShareConnection(QObject* parent)
    : QObject{parent}
{

}

const QString& NetShareConnection::url() const
{
    return m_url;
}

void NetShareConnection::setUrl(const QString& newUrl)
{
    m_url = newUrl;
}

const QString& NetShareConnection::userName() const
{
    return m_userName;
}

void NetShareConnection::setUserName(const QString& newUserName)
{
    m_userName = newUserName;
}

const QString& NetShareConnection::password() const
{
    return m_password;
}

void NetShareConnection::setPassword(const QString& newPassword)
{
    m_password = newPassword;
}

bool NetShareConnection::startConnect()
{
    NETRESOURCE net;

    net.dwType = RESOURCETYPE_ANY;

    net.lpLocalName = NULL;
    net.lpRemoteName = m_url.toStdWString().data();

    net.lpProvider = NULL;

    DWORD err;
    err = WNetAddConnection2(&net, m_password.toStdWString().data(),
                             m_userName.toStdWString().data(), CONNECT_UPDATE_PROFILE);
    m_isConnected = err == NO_ERROR;
    qDebug() << err;
    return m_isConnected;
}

bool NetShareConnection::endConnect()
{

    return true;


}

bool NetShareConnection::isConnected() const
{
    return m_isConnected;
}

void NetShareConnection::setIsConnected(bool newIsConnected)
{
    m_isConnected = newIsConnected;
}
