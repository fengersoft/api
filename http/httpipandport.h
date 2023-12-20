#ifndef HTTPIPANDPORT_H
#define HTTPIPANDPORT_H

#include <QObject>

class HttpIpAndPort : public QObject
{
    Q_OBJECT
public:
    explicit HttpIpAndPort(QObject* parent = nullptr);

    const QString& ipAndPort() const;
    void setIpAndPort(const QString& newIpAndPort);
    QString ip();
    QString port();

signals:
private:
    QString m_ipAndPort;

};

#endif // HTTPIPANDPORT_H
