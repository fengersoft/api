#include "balancewheelitem.h"

BalanceWheelItem::BalanceWheelItem(QObject *parent)
    : QObject{parent}
{
    m_score=1;
    m_backColor=Qt::white;

}

double BalanceWheelItem::startAngle() const
{
    return m_startAngle;
}

void BalanceWheelItem::setStartAngle(double newStartAngle)
{
    m_startAngle = newStartAngle;
}

double BalanceWheelItem::endAngle() const
{
    return m_endAngle;
}

void BalanceWheelItem::setEndAngle(double newEndAngle)
{
    m_endAngle = newEndAngle;
}

int BalanceWheelItem::score() const
{
    return m_score;
}



bool BalanceWheelItem::selected() const
{
    return m_selected;
}

void BalanceWheelItem::setSelected(bool newSelected)
{
    m_selected = newSelected;
}

const QString &BalanceWheelItem::caption() const
{
    return m_caption;
}

void BalanceWheelItem::setCaption(const QString &newCaption)
{
    m_caption = newCaption;
}

void BalanceWheelItem::setScore(int newScore)
{
    m_score = newScore;
}

const QColor &BalanceWheelItem::backColor() const
{
    return m_backColor;
}

void BalanceWheelItem::setBackColor(const QColor &newBackColor)
{
    m_backColor = newBackColor;
}


