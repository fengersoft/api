#ifndef WEBAPI_H
#define WEBAPI_H

#include <QObject>
#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include "../api/http/synchttpobject.h"
#include "../api/global/globaldata.h"

void post_ResultAsJsonArray(QString rPath, QJsonArray& jarr);
void post_ResultAsJsonArray(QString rPath, QJsonObject& jobj, QJsonArray& jarr);
void post_ResultAsJsonObject(QString rPath, QJsonObject& jobj, QJsonObject& jret);
void post_ResultAsByteArray(QString rPath, QJsonObject& jobj, QByteArray& retData);
void post_ResultAsJsonObject(QString rPath, QJsonArray& jarr, QJsonObject& jret);
void post_ResultAsJsonObject(QString rPath, QJsonObject& jret);

#endif // WEBAPI_H
