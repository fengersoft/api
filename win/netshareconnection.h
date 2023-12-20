//LIBS+=\
//       -lws2_32 -lmpr
#ifndef NETSHARECONNECTION_H
#define NETSHARECONNECTION_H

#include <QObject>
#include <cstddef>
#include <winerror.h>
#include <winsock2.h>
#include <windows.h>
#include <QDebug>


class NetShareConnection : public QObject
{
    Q_OBJECT
public:
    explicit NetShareConnection(QObject* parent = nullptr);

    const QString& url() const;
    void setUrl(const QString& newUrl);

    const QString& userName() const;
    void setUserName(const QString& newUserName);

    const QString& password() const;
    void setPassword(const QString& newPassword);
    bool startConnect();
    bool endConnect();


    bool isConnected() const;
    void setIsConnected(bool newIsConnected);

signals:
private:
    QString m_url;
    QString m_userName;
    QString m_password;
    bool m_isConnected;


};

#endif // NETSHARECONNECTION_H
