#include "randommappointdistance.h"

RandomMapPointDistance::RandomMapPointDistance(QObject *parent)
    : QObject{parent}
{

}

RandomMapPoint *RandomMapPointDistance::startPoint() const
{
    return m_startPoint;
}

void RandomMapPointDistance::setStartPoint(RandomMapPoint *newStartPoint)
{
    m_startPoint = newStartPoint;
}

RandomMapPoint *RandomMapPointDistance::endPoint() const
{
    return m_endPoint;
}

void RandomMapPointDistance::setEndPoint(RandomMapPoint *newEndPoint)
{
    m_endPoint = newEndPoint;
}

double RandomMapPointDistance::distance() const
{
    return m_distance;
}

void RandomMapPointDistance::setDistance(double newDistance)
{
    m_distance = newDistance;
}

double calcRandomMapPointDistance(RandomMapPoint *pt1, RandomMapPoint *pt2)
{
    int l1=abs(pt1->x()-pt2->x());
    int l2=abs(pt1->y()-pt2->y());
    return std::sqrt(l1*l1+l2*l2);

}
