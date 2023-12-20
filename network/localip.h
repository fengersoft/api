#ifndef LOCALIP_H
#define LOCALIP_H

#include <QObject>
#include <QNetworkInterface>
#include <QSharedPointer>

class LocalIp : public QObject
{
    Q_OBJECT
public:
    explicit LocalIp(QObject* parent = nullptr);
    static QSharedPointer<LocalIp> m_localIp;
    static LocalIp* instance();

    QString ips() const;
    void setIps(const QString& newIps);

signals:
private:
    QString m_ips;

};
LocalIp* localIp();

#endif // LOCALIP_H
