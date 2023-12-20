#ifndef FNDATETIME_H
#define FNDATETIME_H

#include <QObject>
#include <QDate>
#include <QTime>

QString secondToString(int i);
QString fnFormatDate(QString s);
QString fnFormatDate2(QString s);
QString fnFormatDate3(QString s);
QString fnEncodeDateTimeStr(int year, int month, int day, int hour, int minute);
QDate fnEncodeDate(int year, int month, int day);
QTime fnEncodeTime(int hour, int minute);
QString fnEncodeTimeStr(int hour, int minute);
#endif // FNDATETIME_H
