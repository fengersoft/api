#include "drawobject.h"

DrawObject::DrawObject(QObject* parent) : QObject(parent)
{

}

void DrawObject::retSetPoints(QPoint& pt1, QPoint& pt2)
{
    int x1 = pt1.x();
    int y1 = pt1.y();

    int x2 = pt2.x();
    int y2 = pt2.y();

    if (x1 > x2)
    {
        int x = x1;
        x1 = x2;
        x2 = x;
    }
    if (y1 > y2)
    {
        int y = y1;
        y1 = y2;
        y2 = y;
    }
    pt1 = QPoint(x1, y1);
    pt2 = QPoint(x2, y2);

}


