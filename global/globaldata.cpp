#include "globaldata.h"
#include "qcryptographichash.h"
#include "qfileinfo.h"
QString GlobalData::qssText = "";
QString GlobalData::areacode = "";
QString GlobalData::userName = "";
QString GlobalData::password = "";
QString GlobalData::baseUrl = "";
QString GlobalData::loginName = "";
QString GlobalData::userRoleName = "";
QString GlobalData::uid = "";
int GlobalData::userId = -1;
QString GlobalData::fileServerIp = "127.0.0.1";
QString GlobalData::fileServerPort = "1480";
bool GlobalData::searchGlobal = true;
bool GlobalData::threeMember = false;
bool GlobalData::repalceBzbh = false;
QString GlobalData::aesKey = "hxyz2023";
QString GlobalData::tokenValue = "";
QString GlobalData::tokenName = "token";
bool GlobalData::showChildNode = false;
bool GlobalData::fuzzyMatch = true;
int  GlobalData::defaultDisplayRows = 400;
bool GlobalData::showNumberLimit = false;
int GlobalData::selectOrderType1 = 0;
bool GlobalData::isShowWaterMark = false;
QString GlobalData::waterMarkText = "";
bool GlobalData::isShowBzztWhenOpenPdf = false;

QString GlobalData::fileManagementUrl = "";
QString GlobalData::storeMonitorUrl = "";
QString GlobalData::storeMonitorWebSocketUrl = "";
QString GlobalData::storeMonitorWebApiUrl = "";
QString GlobalData::storeMonitorWebUrl = "";
QString GlobalData::storeId = "";
int GlobalData::cameraCols = 3;
int GlobalData::cameraRows = 3;
QColor GlobalData::backgroundColor = QColor(245, 246, 254);
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

QString newNoDashUuid()
{
    QUuid uuid = QUuid::createUuid();
    QString ret = uuid.toString();
    ret = ret.replace("{", "");
    ret = ret.replace("}", "");
    ret = ret.replace("-", "");
    return ret;
}

QString newDashUuid()
{
    QUuid uuid = QUuid::createUuid();
    QString ret = uuid.toString();
    ret = ret.replace("{", "");
    ret = ret.replace("}", "");
    return ret;
}

QString fileUuid(QFileInfo& info)
{
    if (!info.exists())
    {
        return "";
    }

    QString s = info.fileName() + "|" + QString("%1").arg(info.size());

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(s.toLocal8Bit());
    QString uuid = md5.result().toHex().toLower();
    return uuid;

}

QString fileUuid(QString filePath)
{
    QFileInfo info(filePath);
    return fileUuid(info);

}

QString filePathUuid(QFileInfo& info)
{
    if (!info.exists())
    {
        return "";
    }

    QString s = info.absoluteFilePath() + "|" + info.lastModified().toString("yyyy-MM-dd hh:mm:ss") + "|" + QString("%1").arg(info.size());

    QCryptographicHash md5(QCryptographicHash::Md5);
    md5.addData(s.toLocal8Bit());
    QString uuid = md5.result().toHex().toLower();
    return uuid;

}

QString filePathUuid(QString filePath)
{
    QFileInfo info(filePath);
    return filePathUuid(info);


}

QString GlobalData::currentDate()
{
    QDate d=QDate::currentDate();
    return d.toString("yyyy-MM-dd");

}
