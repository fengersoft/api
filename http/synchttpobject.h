#ifndef SYNCHTTPOBJECT_H
#define SYNCHTTPOBJECT_H

#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include "../api/global/globaldata.h"

#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#include <QTextCodec>
#else
#include <QtCore5Compat/QTextCodec>
#endif
#include <QWidget>

class SyncHttpObject : public QObject
{
    Q_OBJECT
public:
    explicit SyncHttpObject(QWidget* parent = nullptr);
    bool downloadFile(QString url, QString path);
    int postJsonData(const QString& params, QByteArray& data, QByteArray& ret);
    void setIpAndPort(const QString& ip, int port, QString protocol = "http");
    int postJsonDataByUrl(const QString& url, QByteArray& data, QByteArray& ret);
    int postData(const QString& params, QByteArray& data, QByteArray& ret);
    int getJsonDataByUrl(const QString& url, QByteArray& ret);
    int getJsonData(const QString& params, QByteArray& ret);
    int postJsonArrayByUrl(const QString& url, QJsonArray& jarr);
    int postJsonArrayByUrl(const QString& url, QJsonObject& jobj, QJsonArray& jarr);

    int postJsonObjectByUrl(const QString& url, QJsonObject& jobj, QJsonObject& jret);
    int postJsonObjectByUrl(const QString& url, QJsonArray& jarr, QJsonObject& jret);
    int postJsonObjectByUrl(const QString& url, QJsonObject& jobj, QByteArray& bret);
    int postJsonObjectByUrl(const QString& url, QJsonObject& jret);
    int getJsonObjectByUrl(const QString& url, QJsonObject& jret);
    int getHtmlData(const QString& url, QByteArray& ret);
    int getHtmlDataByUrl(const QString& url, QByteArray& ret);
    void setBaseUrl(QString baseUrl);
signals:

private:
    QString m_baseUrl;
};
int getHtmlData(QWidget* parent, const QString& url, QByteArray& ret);
#endif // SYNCHTTPOBJECT_H
