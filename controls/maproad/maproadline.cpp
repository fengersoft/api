#include "maproadline.h"

MapRoadLine::MapRoadLine(QObject *parent)
    : QObject{parent}
{

}

MapRoadPoint *MapRoadLine::startPoint() const
{
    return m_startPoint;
}

void MapRoadLine::setStartPoint(MapRoadPoint *newStartPoint)
{
    m_startPoint = newStartPoint;
}

MapRoadPoint *MapRoadLine::endPoint() const
{
    return m_endPoint;
}

void MapRoadLine::setEndPoint(MapRoadPoint *newEndPoint)
{
    m_endPoint = newEndPoint;
}
