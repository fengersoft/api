#ifndef RANDOMMAPPOINT_H
#define RANDOMMAPPOINT_H

#include <QObject>
#include "randommappointdistance.h"
#include <QPolygon>
#include <QDebug>

enum RandomMapPointType
{
    PtCenter,
    PtBorder,
    PtNone
};
class RandomMapPointDistance;
class RandomMapPoint : public QObject
{
    Q_OBJECT
public:
    explicit RandomMapPoint(QObject *parent = nullptr);

    int x() const;
    void setX(int newX);

    int y() const;
    void setY(int newY);

    int pointCount() const;
    void setPointCount(int newPointCount);
     QList<RandomMapPointDistance*> pointDistances;
    RandomMapPointType pointType() const;
    void setPointType(RandomMapPointType newPointType);
    void getArea();
    QList<RandomMapPoint*> roundPoints;
    QPoint point();
    void getSelectPoints(int k);

    double centerX() const;
    void setCenterX(double newCenterX);

    double centerY() const;
    void setCenterY(double newCenterY);

    int colIndex() const;
    void setColIndex(int newColIndex);

    int rowIndex() const;
    void setRowIndex(int newRowIndex);

signals:
private:
    int m_x;
    int m_y;
    int m_pointCount;
    RandomMapPointType m_pointType;
    double m_centerX;
    double m_centerY;
    int m_colIndex;
    int m_rowIndex;


};

#endif // RANDOMMAPPOINT_H
