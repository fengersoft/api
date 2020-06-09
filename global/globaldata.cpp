#include "globaldata.h"
QString GlobalData::qssText = "";
QString GlobalData::areacode = "";
QString GlobalData::userName = "";
QString GlobalData::password = "";
QString GlobalData::rootUrl = "";
GlobalData::GlobalData(QObject* parent)
    : QObject(parent)
{
}
