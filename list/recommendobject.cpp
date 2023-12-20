#include "recommendobject.h"
#include "qdatetime.h"

RecommendObject::RecommendObject(QObject* parent)
    : QObject{parent}
{
    m_selectedCount = 0;
    m_latestSelectedTime = QDateTime::fromString("2000-01-01 00:00:00", "yyyy-MM-dd hh:mm:ss");

}

const QString& RecommendObject::name() const
{
    return m_name;
}

void RecommendObject::setName(const QString& newName)
{
    m_name = newName;
}



const QDateTime& RecommendObject::latestSelectedTime() const
{
    return m_latestSelectedTime;
}

void RecommendObject::setLatestSelectedTime(const QDateTime& newLatestSelectedTime)
{
    m_latestSelectedTime = newLatestSelectedTime;
}

int RecommendObject::selectedCount() const
{
    return m_selectedCount;
}

void RecommendObject::setSelectedCount(int newSelectedCount)
{
    m_selectedCount = newSelectedCount;
}

void RecommendObject::incSelectedCount()
{
    m_selectedCount++;
    m_latestSelectedTime = QDateTime::currentDateTime();

}

const QRect &RecommendObject::rect() const
{
    return m_rect;
}

void RecommendObject::setRect(const QRect &newRect)
{
    m_rect = newRect;
}


