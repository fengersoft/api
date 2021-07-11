#include "synchttpobject.h"

SyncHttpObject::SyncHttpObject(QWidget* parent)
    : QObject(parent)
{
}

bool SyncHttpObject::downloadFile(QString url, QString path)
{
    return true;
}

void SyncHttpObject::setIpAndPort(const QString& ip, int port, QString protocol)
{
    m_baseUrl = QString("%1://%2:%3/").arg(protocol).arg(ip).arg(port);
    qDebug() << m_baseUrl;
}

int SyncHttpObject::postJsonData(const QString& params, QByteArray& data, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    qDebug() << m_baseUrl + params;
    requet.setUrl(QUrl(m_baseUrl + params));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->post(requet, data);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;
}

int SyncHttpObject::postData(const QString& params, QByteArray& data, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    qDebug() << m_baseUrl + params;
    requet.setUrl(QUrl(m_baseUrl + params));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QNetworkReply* reply = manager->post(requet, data);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;
}

int SyncHttpObject::getJsonData(const QString& params, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(m_baseUrl + params));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply* reply = manager->get(requet);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;
}

int SyncHttpObject::getHtmlData(const QString& url, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    qDebug() << url;
    QNetworkReply* reply = manager->get(requet);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    ret = reply->readAll();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    delete reply;
    delete manager;
    return code;
}

void SyncHttpObject::setBaseUrl(QString baseUrl)
{
    m_baseUrl = baseUrl;
}

int getHtmlData(QWidget* parent, const QString& url, QByteArray& ret)
{
    qDebug() << url;
    SyncHttpObject* http = new SyncHttpObject(parent);
    int code = http->getHtmlData(url, ret);

    delete http;
    return code;
}
