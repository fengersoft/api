#include "globaldata.h"
QString GlobalData::qssText = "";
QString GlobalData::areacode = "";
QString GlobalData::userName = "";
QString GlobalData::password = "";
QString GlobalData::baseUrl = "";
QString GlobalData::uid = "";
GlobalData::GlobalData(QObject* parent)
    : QObject(parent)
{
}

QString GlobalData::createUuid()
{
    QUuid uuid = QUuid::createUuid();
    QString ret = uuid.toString();
    ret = ret.replace("{", "");
    ret = ret.replace("}", "");
    return ret;
}
