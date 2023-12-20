#ifndef MAPROADLINE_H
#define MAPROADLINE_H

#include <QObject>
#include "maproadpoint.h"

class MapRoadLine : public QObject
{
    Q_OBJECT
public:
    explicit MapRoadLine(QObject* parent = nullptr);

    MapRoadPoint* startPoint() const;
    void setStartPoint(MapRoadPoint* newStartPoint);

    MapRoadPoint* endPoint() const;
    void setEndPoint(MapRoadPoint* newEndPoint);

signals:
private:
    MapRoadPoint* m_startPoint;
    MapRoadPoint* m_endPoint;

};

#endif // MAPROADLINE_H
