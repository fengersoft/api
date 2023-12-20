
#ifndef HTTPWEBSERVER_H
#define HTTPWEBSERVER_H


#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>

#include "requestparser.h"


class HttpWebServer : public QObject
{
    Q_OBJECT
public:
    explicit HttpWebServer(QObject* parent = nullptr);

    QTcpServer* server() const;
    void setServer(QTcpServer* newServer);

    int port() const;
    void setPort(int newPort);
    void startServer(int port);

    QString defaultPagePath() const;
    void setDefaultPagePath(const QString& newDefaultPagePath);

    QStringList rootPaths() const;
    void setRootPaths(const QStringList& newRootPaths);
    void addRootPath(QString path);
    QString getServerFilePathName(QString pathName);
    void sendServerData(QFileInfo& fileInfo, QTcpSocket* socket,
                        QString dataType, QString suffix);

signals:
    bool processRequest(RequestParser* paser, QTcpSocket* socket);
public slots:
    void onNewConnection();
    void onClientReadyRead();
    QString getContextType(QString suffix);
private:
    QTcpServer* m_server;
    int m_port;
    QString m_defaultPagePath;
    QStringList m_rootPaths;
    QSet<QString> m_imageSuffixes;

};

#endif // HTTPWEBSERVER_H
