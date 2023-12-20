
#ifndef REMINDITEM_H
#define REMINDITEM_H


#include <QObject>
#include <QDateTime>


class ReMindItem : public QObject
{
    Q_OBJECT
public:
    explicit ReMindItem(QObject* parent = nullptr);

    int year() const;
    void setYear(int newYear);

    int month() const;
    void setMonth(int newMonth);

    QString info() const;
    void setInfo(const QString& newInfo);

    int day() const;
    void setDay(int newDay);

    int hour() const;
    void setHour(int newHour);

    int minute() const;
    void setMinute(int newMinute);

    QString infoType() const;
    void setInfoType(const QString& newInfoType);
    bool isToTime(QDateTime datetime, int beforeMinute, int pastMinute);

signals:
private:
    QString m_info;
    QString m_infoType;
    int m_year;
    int m_month;
    int m_day;
    int m_hour;
    int m_minute;

};
bool fnIsToTime(QDateTime datetime, int year, int month, int day, int hour, int minute, int beforeMinute, int pastMinute);

#endif // REMINDITEM_H
