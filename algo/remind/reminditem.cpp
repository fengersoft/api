
#include "reminditem.h"

ReMindItem::ReMindItem(QObject* parent)
    : QObject{parent}
{

}

int ReMindItem::year() const
{
    return m_year;
}

void ReMindItem::setYear(int newYear)
{
    m_year = newYear;
}

int ReMindItem::month() const
{
    return m_month;
}

void ReMindItem::setMonth(int newMonth)
{
    m_month = newMonth;
}

QString ReMindItem::info() const
{
    return m_info;
}

void ReMindItem::setInfo(const QString& newInfo)
{
    m_info = newInfo;
}

int ReMindItem::day() const
{
    return m_day;
}

void ReMindItem::setDay(int newDay)
{
    m_day = newDay;
}

int ReMindItem::hour() const
{
    return m_hour;
}

void ReMindItem::setHour(int newHour)
{
    m_hour = newHour;
}

int ReMindItem::minute() const
{
    return m_minute;
}

void ReMindItem::setMinute(int newMinute)
{
    m_minute = newMinute;
}

QString ReMindItem::infoType() const
{
    return m_infoType;
}

void ReMindItem::setInfoType(const QString& newInfoType)
{
    m_infoType = newInfoType;
}

bool ReMindItem::isToTime(QDateTime datetime, int beforeMinute, int pastMinute)
{

    return fnIsToTime(datetime, m_year, m_month, m_day, m_hour, m_minute, beforeMinute, pastMinute);


}


bool fnIsToTime(QDateTime datetime, int year, int month, int day, int hour, int minute, int beforeMinute, int pastMinute)
{
    if (datetime.date().year() != year)
    {
        return false;
    }
    if (datetime.date().month() != month)
    {
        return false;
    }
    if (datetime.date().day() != day)
    {
        return false;
    }
    int s1 = datetime.time().hour() * 60 + datetime.time().minute();
    int s2 = hour * 60 + minute;
    if (s2 - s1 > beforeMinute)
    {
        return false;
    }
    if (s1 - s2 > pastMinute)
    {
        return false;
    }

    return true;

}
