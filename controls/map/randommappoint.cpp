#include "randommappoint.h"

RandomMapPoint::RandomMapPoint(QObject *parent)
    : QObject{parent}
{
    m_pointType=PtNone;

}

int RandomMapPoint::x() const
{
    return m_x;
}

void RandomMapPoint::setX(int newX)
{
    m_x = newX;
}

int RandomMapPoint::y() const
{
    return m_y;
}

void RandomMapPoint::setY(int newY)
{
    m_y = newY;
}

int RandomMapPoint::pointCount() const
{
    return m_pointCount;
}

void RandomMapPoint::setPointCount(int newPointCount)
{
    m_pointCount = newPointCount;
}

RandomMapPointType RandomMapPoint::pointType() const
{
    return m_pointType;
}

void RandomMapPoint::setPointType(RandomMapPointType newPointType)
{
    m_pointType = newPointType;
}

void RandomMapPoint::getArea()
{
    std::sort(pointDistances.begin(),pointDistances.end(),
          [](RandomMapPointDistance *pt1,RandomMapPointDistance*pt2)
          {
                  return pt1->distance()<pt2->distance();
          });
    QPoint curPt=point();

        int i=0;
        while (true) {

            getSelectPoints(i);

            QPolygon pol;
            for (int j=0;j<roundPoints.count();j++)
            {
                pol<<roundPoints[j]->point();

            }
            if (pol.contains(curPt))
            {
                for (int j=0;j<roundPoints.count();j++)
                {
                    roundPoints[j]->setPointType(PtBorder);

                }
                setPointType(PtCenter);
                break;
            }else
            {
                roundPoints.clear();
                i++;
            }
            qDebug()<<pol<<curPt;
            if (i>10)
            break;



        }




}

QPoint RandomMapPoint::point()
{
    return QPoint(m_x,m_y);

}

void RandomMapPoint::getSelectPoints(int k)
{
    int n=0;
    int i=k;
    while(n<m_pointCount)
    {
        if (i==(pointDistances.count()-1))
        {
            break;
        }
        if (pointDistances[i]->endPoint()->pointType()==PtCenter)
        {
        }else
        {
            roundPoints<<pointDistances[i]->endPoint();
            n++;
        }

        i++;
    }

}

double RandomMapPoint::centerX() const
{
    return m_centerX;
}

void RandomMapPoint::setCenterX(double newCenterX)
{
    m_centerX = newCenterX;
}

double RandomMapPoint::centerY() const
{
    return m_centerY;
}

void RandomMapPoint::setCenterY(double newCenterY)
{
    m_centerY = newCenterY;
}

int RandomMapPoint::colIndex() const
{
    return m_colIndex;
}

void RandomMapPoint::setColIndex(int newColIndex)
{
    m_colIndex = newColIndex;
}

int RandomMapPoint::rowIndex() const
{
    return m_rowIndex;
}

void RandomMapPoint::setRowIndex(int newRowIndex)
{
    m_rowIndex = newRowIndex;
}
