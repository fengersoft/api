#include "drawobject.h"

DrawObject::DrawObject(QObject* parent) : QObject(parent)
{

}

void DrawObject::reSetPoints(QPoint& pt1, QPoint& pt2)
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

int DrawObject::pointsXDistance(QPoint& pt1, QPoint& pt2)
{
    return abs(pt1.x() - pt2.x());

}

int DrawObject::pointsYDistance(QPoint& pt1, QPoint& pt2)
{
    return abs(pt1.y() - pt2.y());

}

void DrawObject::drawRect(QPainter& painter, QPoint& pt1, QPoint& pt2)
{
    QPoint p1 = pt1;
    QPoint p2 = pt2;
    reSetPoints(p1, p2);
    painter.drawLine(pt1.x(), pt1.y(), pt2.x(), pt1.y());
    painter.drawLine(pt1.x(), pt1.y(), pt1.x(), pt2.y());

    painter.drawLine(pt1.x(), pt2.y(), pt2.x(), pt2.y());
    painter.drawLine(pt2.x(), pt1.y(), pt2.x(), pt2.y());

}

void DrawObject::drawRect(QPainter& painter, int startX, int startY, QRect rc)
{

    QRect newRc = QRect(startX + rc.x(), startY + rc.y(), rc.width(), rc.height());
    painter.drawRect(newRc);

}

void DrawObject::drawRect(QPainter& painter, int startX, int startY, QPoint center, int width, int height)
{

    QRect rc = QRect(startX + center.x() - width / 2, startY + center.y() - height / 2, width, height);
    painter.drawRect(rc);
}

void DrawObject::drawPixmap(QPainter& painter, int startX, int startY, QRect rc, QPixmap& pix)
{
    QRect newRc = QRect(startX + rc.x(), startY + rc.y(), rc.width(), rc.height());
    painter.drawPixmap(newRc, pix, pix.rect());
}

void DrawObject::drawPixmap(QPainter& painter, int startX, int startY, QPoint center, int width, int height, QPixmap& pix)
{
    QRect rc = QRect(startX + center.x() - width / 2, startY + center.y() - height / 2, width, height);
    painter.drawPixmap(rc, pix, pix.rect());
}

void DrawObject::drawPixmap(QPainter& painter, double angle, int startX, int startY, QPoint center, int width, int height, QPixmap& pix)
{
    painter.translate(startX + center.x(), startY + center.y());
    painter.rotate(angle);
    QRect rc = QRect(- width / 2, - height / 2, width, height);
    painter.drawPixmap(rc, pix, pix.rect());
}

void DrawObject::drawLine(QPainter& painter, int startX, int startY, QPoint pt1, QPoint pt2)
{
    QPoint p1 = QPoint(pt1.x() + startX, pt1.y() + startY);
    QPoint p2 = QPoint(pt2.x() + startX, pt2.y() + startY);
    painter.drawLine(p1, p2);

}

void DrawObject::drawStraightLine(QPainter& painter, QPoint& pt1, QPoint pt2)
{
    int x = abs(pt1.x() - pt2.x());
    int y = abs(pt1.y() - pt2.y());
    if (x > y)
    {
        painter.drawLine(pt1.x(), pt1.y(), pt2.x(), pt1.y());
    }
    else
    {
        painter.drawLine(pt1.x(), pt1.y(), pt1.x(), pt2.y());
    }

}

QPoint DrawObject::getStraightLineEndPoint(QPoint& pt1, QPoint pt2)
{
    int x = abs(pt1.x() - pt2.x());
    int y = abs(pt1.y() - pt2.y());
    if (x > y)
    {
        return QPoint(pt2.x(), pt1.y());
    }
    else
    {
        return QPoint(pt1.x(), pt2.y());
    }
}

QPoint DrawObject::getTwoPointsCenter(QPoint& pt1, QPoint pt2)
{
    return QPoint((pt1.x() + pt2.x()) / 2, (pt1.y() + pt2.y()) / 2);
}

int DrawObject::getTwoPointsDistance(QPoint& pt1, QPoint pt2)
{
    return sqrt((pt1.x() - pt2.x()) * (pt1.x() - pt2.x()) + (pt1.y() - pt2.y()) * (pt1.y() - pt2.y()));
}

bool DrawObject::rectContainsPoint(int startX, int startY, QRect& rc, QPoint& pt)
{
    QRect newRc = QRect(rc.left() + startX, rc.top() + startY, rc.width(), rc.height());
    return newRc.contains(pt);
}

int DrawObject::rectAreaSize(QRect& rect)
{
    return rect.width() * rect.height();
}

void DrawObject::resetRect(QRect& rc, QPoint center, int width, int height)
{
    rc = QRect(center.x() - width / 2, center.y() - height / 2, width, height);
}

double DrawObject::radianToAngle(double d)
{
    return d * (180 / 3.141592653);
}

double DrawObject::angleToRadian(double d)
{
    return d * (3.141592653 / 180);
}


