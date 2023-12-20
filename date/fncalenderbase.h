#ifndef FNCALENDERBASE_H
#define FNCALENDERBASE_H

#include <QObject>
#include <QWidget>
#include <QDate>
#include "lunar.h"
struct FnCalenderData
{
    int line;
    int year;
    int month;
    int day;
    int i;
    int j;
    QRect rc;
    QRectF rcf;
    QDate date;
    QString lunarDate;
    QString lunarDay;
    bool isNull = false;
    QString shortDateLabel;
    QColor backgroundColor;
    QString yyyyMMdd;
    bool isSelected;
    int num = 0;
    QStringList remarkNames;
    QString dataType;
};

#endif // FNCALENDERBASE_H
