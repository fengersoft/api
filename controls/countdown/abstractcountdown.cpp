#include "abstractcountdown.h"
#include "qdatetime.h"
#include "qdebug.h"
#include "qpixmap.h"
#include "qtimer.h"
#include "qwindowdefs.h"
#include <cmath>

AbstractCountDown::AbstractCountDown(QWidget* parent)
    : QWidget{parent}
{
    m_percent = 0;
    m_countDownType = CountDownType::CtMinute;
    m_ringBackGround = QPixmap();
    m_snapRingBackGround = QPixmap();
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &AbstractCountDown::onTimeOut);
    m_timer->start(1000);
}

CountDownType AbstractCountDown::countDownType() const
{
    return m_countDownType;
}

void AbstractCountDown::setCountDownType(CountDownType newCountDownType)
{
    m_countDownType = newCountDownType;
}

const QDateTime& AbstractCountDown::startDateTime() const
{
    return m_startDateTime;
}

void AbstractCountDown::setStartDateTime(const QDateTime& newStartDateTime)
{
    m_startDateTime = newStartDateTime;
}

const QDateTime& AbstractCountDown::endDateTime() const
{
    return m_endDateTime;
}

void AbstractCountDown::setEndDateTime(const QDateTime& newEndDateTime)
{
    m_endDateTime = newEndDateTime;
}

const QPixmap& AbstractCountDown::ringBackGround() const
{
    return m_ringBackGround;
}

void AbstractCountDown::setRingBackGround(const QPixmap& newRingBackGround)
{
    m_ringBackGround = newRingBackGround;
    update();
}

int AbstractCountDown::percent() const
{
    return m_percent;
}

void AbstractCountDown::setPercent(int newPercent)
{
    m_percent = newPercent;
}

QTimer* AbstractCountDown::timer() const
{
    return m_timer;
}

void AbstractCountDown::setTimer(QTimer* newTimer)
{
    m_timer = newTimer;
}

QString AbstractCountDown::remainingTimeInfo()
{
    QDateTime curTime = QDateTime::currentDateTime();
    int s = curTime.secsTo(m_endDateTime);
    if (s >= 3600)
    {
        int h = std::trunc(s / 3600);
        s = s - (h * 3600);
        int m = std::trunc(s / 60);
        s = s - m * 60;
        int ms = s;
        return QString("%1小时%2分%3秒 ").arg(h, 2, 10, QLatin1Char('0')).arg(m, 2, 10, QLatin1Char('0')).arg(ms, 2, 10, QLatin1Char('0'));

    }
    else if (s > 60)
    {
        int m = std::trunc(s / 60);
        s = s - m * 60;
        int ms = s;
        return QString("%1分%2秒 ").arg(m, 2, 10, QLatin1Char('0')).arg(ms, 2, 10, QLatin1Char('0'));

    }
    else if (s > 0)
    {
        return QString("%1秒").arg(s, 2, 10, QLatin1Char('0'));
    }
    else
    {
        return "0秒";
    }

}

void AbstractCountDown::onTimeOut()
{
    int m = m_startDateTime.secsTo(m_endDateTime);
    if (m == 0)
    {
        m_percent = 0;
        return;
    }
    QDateTime curTime = QDateTime::currentDateTime();


    int n = m_startDateTime.secsTo(curTime);
    m_percent = std::trunc(100 * (n) / m);
    if (m_percent > 100)
    {
        m_percent = 100;
    }

    update();
}

const QString& AbstractCountDown::title() const
{
    return m_title;
}

void AbstractCountDown::setTitle(const QString& newTitle)
{
    m_title = newTitle;
    update();
}

void AbstractCountDown::resizeEvent(QResizeEvent* event)
{
    m_snapRingBackGround = m_ringBackGround.scaled(width(), height());
    update();


}
