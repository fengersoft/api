#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include "qfileinfo.h"
#include <QObject>
#include <QUuid>
#include <QCryptographicHash>
#include <QDateTime>
#include <QColor>

class GlobalData : public QObject
{
    Q_OBJECT
public:
    explicit GlobalData(QObject* parent = nullptr);
    static QString qssText;
    static QString areacode;
    static QString userName;
    static QString loginName;
    static QString userRoleName;
    static QString uid;
    static int userId;
    static QString password;
    static QString baseUrl;
    static QString fileServerIp;
    static QString fileServerPort;
    static QString aesKey;
    static bool threeMember;
    static bool searchGlobal;
    static bool repalceBzbh;
    static QString tokenName;
    static QString tokenValue;
    static bool showChildNode;
    static bool fuzzyMatch;
    static int defaultDisplayRows;
    static bool showNumberLimit;
    static int selectOrderType1;
    static bool isShowWaterMark;
    static QString waterMarkText;
    static bool isShowBzztWhenOpenPdf;
    static QString fileManagementUrl;
    static QString storeId;
    static QString storeMonitorUrl;
    static QString storeMonitorWebUrl;
    static QString storeMonitorWebSocketUrl;
    static QString storeMonitorWebApiUrl;
    static int cameraCols;
    static int cameraRows;
    static QColor backgroundColor;
    static QString createUuid();
    static QString currentDate();
signals:
};
QString newNoDashUuid();
QString newDashUuid();
QString fileUuid(QFileInfo& info);
QString filePathUuid(QFileInfo& info);
QString filePathUuid(QString filePath);
QString fileUuid(QString filePath);
#endif // GLOBALDATA_H
