#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QObject>

class GlobalData : public QObject {
    Q_OBJECT
public:
    explicit GlobalData(QObject* parent = nullptr);
    static QString qssText;
    static QString areacode;
    static QString userName;
    static QString password;
    static QString rootUrl;
signals:
};

#endif // GLOBALDATA_H
