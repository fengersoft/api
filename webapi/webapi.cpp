#include "webapi.h"


void post_ResultAsJsonArray(QString rPath, QJsonArray& jarr)
{
    qDebug() << GlobalData::baseUrl + rPath;
    SyncHttpObject* http = new SyncHttpObject();
    http->postJsonArrayByUrl(GlobalData::baseUrl + rPath, jarr);
    qDebug() << GlobalData::baseUrl << rPath << jarr;

    delete http;

}

void post_ResultAsJsonArray(QString rPath, QJsonObject& jobj, QJsonArray& jarr)
{
    qDebug() << jobj;
    qDebug() << GlobalData::baseUrl + rPath;
    SyncHttpObject* http = new SyncHttpObject();
    http->postJsonArrayByUrl(GlobalData::baseUrl + rPath, jobj, jarr);
    qDebug() << rPath << jarr;

    delete http;

}


void post_ResultAsJsonObject(QString rPath, QJsonObject& jobj, QJsonObject& jret)
{
    qDebug() << jobj;
    SyncHttpObject* http = new SyncHttpObject();
    http->postJsonObjectByUrl(GlobalData::baseUrl + rPath, jobj, jret);
    qDebug() << rPath << jret;

    delete http;

}

void post_ResultAsJsonObject(QString rPath, QJsonObject& jret)
{
    SyncHttpObject* http = new SyncHttpObject();
    http->postJsonObjectByUrl(GlobalData::baseUrl + rPath, jret);
    qDebug() << rPath << jret;

    delete http;

}

void post_ResultAsJsonObject(QString rPath, QJsonArray& jarr, QJsonObject& jret)
{
    SyncHttpObject* http = new SyncHttpObject();
    http->postJsonObjectByUrl(GlobalData::baseUrl + rPath, jarr, jret);
    qDebug() << rPath << jret;

    delete http;

}

void post_ResultAsByteArray(QString rPath, QJsonObject& jobj, QByteArray& retData)
{
    SyncHttpObject* http = new SyncHttpObject();

    http->postJsonObjectByUrl(GlobalData::baseUrl + rPath, jobj, retData);
    qDebug() << rPath ;

    delete http;

}
