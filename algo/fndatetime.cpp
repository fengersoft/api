#include "fndatetime.h"



QString secondToString(int i)
{
    if (i < 60)
    {
        return QString("00:00:%1").arg(i, 2, 10, QLatin1Char('0'));
    }
    else if (i < 3600)
    {
        int n = i % 60;
        int m = (i - n) / 60;
        return QString("00:%1:%2").arg(m, 2).arg(n, 2);

    }
    else
    {
        return "";
    }
}

QString fnFormatDate(QString s)
{
    int n = s.indexOf("T");
    if (n >= 0)
    {
        s = s.left(n);
    }

    return s;
}

QString fnFormatDate2(QString s)
{
    int n = s.indexOf(" ");
    if (n >= 0)
    {
        s = s.left(n);
    }

    return s;

}

QString fnEncodeDateTimeStr(int year, int month, int day, int hour, int minute)
{
    return QString("%1-%2-%3 %4:%5:00").arg(year, 4, 10, QLatin1Char('0'))
           .arg(month, 2, 10, QLatin1Char('0'))
           .arg(day, 2, 10, QLatin1Char('0'))
           .arg(hour, 2, 10, QLatin1Char('0'))
           .arg(minute, 2, 10, QLatin1Char('0'));

}

QDate fnEncodeDate(int year, int month, int day)
{
    QString dateStr = QString("yyyy-MM-dd")
                      .arg(year, 4, 10, QLatin1Char('0'))
                      .arg(month, 2, 10, QLatin1Char('0'))
                      .arg(day, 2, 10, QLatin1Char('0'));
    QDate d = QDate::fromString(dateStr, "yyyy-MM-dd");

    return d;

}

QTime fnEncodeTime(int hour, int minute)
{
    QString timeStr = QString("hh:mm")

                      .arg(hour, 2, 10, QLatin1Char('0'))
                      .arg(minute, 2, 10, QLatin1Char('0'));
    QTime d = QTime::fromString(timeStr, "hh:mm");

    return d;

}

QString fnEncodeTimeStr(int hour, int minute)
{
    return QString("%1:%2")
           .arg(hour, 2, 10, QLatin1Char('0'))
           .arg(minute, 2, 10, QLatin1Char('0'));

}

QString fnFormatDate3(QString s)
{
    int n = s.indexOf(".");
    QString s1 = s.left(n);
    s1 = s1.replace("T", " ");
    return s1;

}
