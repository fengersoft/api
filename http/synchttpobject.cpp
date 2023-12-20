#include "synchttpobject.h"
#include "qjsonobject.h"

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
    QString url = m_baseUrl + params;
    return postJsonDataByUrl(url, data, ret);

}

int SyncHttpObject::postJsonDataByUrl(const QString& url, QByteArray& data, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;

    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }

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
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
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
    QString url = m_baseUrl + params;

    return getJsonDataByUrl(url, ret);
}

int SyncHttpObject::getJsonDataByUrl(const QString& url, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
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

int SyncHttpObject::postJsonArrayByUrl(const QString& url, QJsonArray& jarr)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
    QByteArray input = QByteArray();
    QNetworkReply* reply = manager->post(requet, input);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray data = reply->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    jarr = jdoc.array();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();
    delete manager;
    return code;

}

int SyncHttpObject::postJsonArrayByUrl(const QString& url, QJsonObject& jobj, QJsonArray& jarr)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
    QByteArray input;
    QJsonDocument jdoc0;
    jdoc0.setObject(jobj);
    input = jdoc0.toJson();
    QNetworkReply* reply = manager->post(requet, input);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray data = reply->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    jarr = jdoc.array();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();
    delete manager;
    return code;

}

int SyncHttpObject::postJsonObjectByUrl(const QString& url, QJsonObject& jobj, QJsonObject& jret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
    QByteArray input;
    QJsonDocument jdoc0;
    jdoc0.setObject(jobj);
    input = jdoc0.toJson();
    QNetworkReply* reply = manager->post(requet, input);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray data = reply->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    jret = jdoc.object();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();
    delete manager;
    return code;

}

int SyncHttpObject::postJsonObjectByUrl(const QString& url, QJsonArray& jarr, QJsonObject& jret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
    QByteArray input;
    QJsonDocument jdoc0;
    jdoc0.setArray(jarr);
    input = jdoc0.toJson();
    QNetworkReply* reply = manager->post(requet, input);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray data = reply->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    jret = jdoc.object();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();
    delete manager;
    return code;

}

int SyncHttpObject::postJsonObjectByUrl(const QString& url, QJsonObject& jobj, QByteArray& bret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
    QByteArray input;
    QJsonDocument jdoc0;
    jdoc0.setObject(jobj);
    input = jdoc0.toJson();
    QNetworkReply* reply = manager->post(requet, input);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    bret = reply->readAll();

    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();
    delete manager;
    return code;

}

int SyncHttpObject::postJsonObjectByUrl(const QString& url, QJsonObject& jret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
    QByteArray input;

    QNetworkReply* reply = manager->post(requet, input);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray data = reply->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    jret = jdoc.object();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();
    delete manager;
    return code;

}

int SyncHttpObject::getJsonObjectByUrl(const QString& url, QJsonObject& jret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setUrl(QUrl(url));
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }


    QNetworkReply* reply = manager->get(requet);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    QByteArray data = reply->readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    jret = jdoc.object();
    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    reply->deleteLater();
    delete manager;
    return code;

}

int SyncHttpObject::getHtmlData(const QString& url, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }
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

int SyncHttpObject::getHtmlDataByUrl(const QString& url, QByteArray& ret)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest requet;
    requet.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    requet.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/81.0.4044.129 Safari/537.36");
    if (GlobalData::tokenValue != "")
    {
        requet.setRawHeader(GlobalData::tokenName.toLocal8Bit(), GlobalData::tokenValue.toLocal8Bit());
    }

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
