#ifndef CRONDATECHECKER_H
#define CRONDATECHECKER_H

#include "qdatetime.h"
#include <QObject>
#include <QDebug>
#include "../algo/valuespliter.h"

class CronDateChecker : public QObject
{
    Q_OBJECT
public:
    explicit CronDateChecker(QObject* parent = nullptr);

    const QString& year() const;
    void setYear(const QString& newYear);

    const QString& month() const;
    void setMonth(const QString& newMonth);

    const QString& day() const;
    void setDay(const QString& newDay);

    const QString& week() const;
    void setWeek(const QString& newWeek);
    bool validate(QDate date = QDate::currentDate());

signals:
private:
    QString m_year;
    QString m_month;
    QString m_day;
    QString m_week;

};

#endif // CRONDATECHECKER_H
