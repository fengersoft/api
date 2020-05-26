#include "globaldata.h"
QString GlobalData::qssText = "";
QString GlobalData::areacode = "";
GlobalData::GlobalData(QObject* parent)
    : QObject(parent)
{
}
