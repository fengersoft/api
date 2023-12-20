#ifndef RANDOMMAPPOINTDISTANCE_H
#define RANDOMMAPPOINTDISTANCE_H

#include <QObject>
#include "randommappoint.h"
class RandomMapPoint;
class RandomMapPointDistance : public QObject
{
    Q_OBJECT
public:
    explicit RandomMapPointDistance(QObject *parent = nullptr);

    RandomMapPoint *startPoint() const;
    void setStartPoint(RandomMapPoint *newStartPoint);

    RandomMapPoint *endPoint() const;
    void setEndPoint(RandomMapPoint *newEndPoint);

    double distance() const;

    void setDistance(double newDistance);

signals:
private:
    RandomMapPoint *m_startPoint;
    RandomMapPoint *m_endPoint;
    double m_distance;
};
double calcRandomMapPointDistance(RandomMapPoint *pt1,RandomMapPoint *pt2);

#endif // RANDOMMAPPOINTDISTANCE_H
