#include "crondatechecker.h"
#include "qstringliteral.h"

CronDateChecker::CronDateChecker(QObject* parent)
    : QObject{parent}
{
    m_year = "*";
    m_month = "*";
    m_day = "*";
    m_week = "*";

}

const QString& CronDateChecker::year() const
{
    return m_year;
}

void CronDateChecker::setYear(const QString& newYear)
{
    m_year = newYear;
}

const QString& CronDateChecker::month() const
{
    return m_month;
}

void CronDateChecker::setMonth(const QString& newMonth)
{
    m_month = newMonth;
}

const QString& CronDateChecker::day() const
{
    return m_day;
}

void CronDateChecker::setDay(const QString& newDay)
{
    m_day = newDay;
}

const QString& CronDateChecker::week() const
{
    return m_week;
}

void CronDateChecker::setWeek(const QString& newWeek)
{
    m_week = newWeek;
}

bool CronDateChecker::validate(QDate date)
{
    bool ret = true;
    QStringList params;
    QStringList values;
    values << QString("%1").arg(date.year());
    values << QString("%1").arg(date.month());
    values << QString("%1").arg(date.day());
    values << QString("%1").arg(date.dayOfWeek());
    params << m_year << m_month << m_day << m_week;
    ValueSpliter* v = new ValueSpliter(this);
    for (int i = 0; i < params.count(); i++)
    {

        v->setValue(params[i]);
        ret = v->inResultSets(values[i]);
        qDebug() << ret << params[i] << values[i];
        if (!ret)
        {
            ret = false;
            break;

        }

    }

    delete v;
    return ret;

}
