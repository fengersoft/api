#include "maproadpoint.h"

MapRoadPoint::MapRoadPoint(QObject* parent)
    : QObject{parent}
{

}

void MapRoadPoint::addPoint(int x, int y)
{
    m_x = x;
    m_y = y;

}

int MapRoadPoint::x() const
{
    return m_x;
}

void MapRoadPoint::setX(int newX)
{
    m_x = newX;
}

int MapRoadPoint::y() const
{
    return m_y;
}

void MapRoadPoint::setY(int newY)
{
    m_y = newY;
}

const QRect &MapRoadPoint::rect() const
{
    return m_rect;
}

void MapRoadPoint::setRect(const QRect &newRect)
{
    m_rect = newRect;
}
