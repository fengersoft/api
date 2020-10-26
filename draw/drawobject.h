#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <QObject>
#include <QPainter>
#include <math.h>
#include <QtMath>
class DrawObject : public QObject
{
    Q_OBJECT
public:
    explicit DrawObject(QObject* parent = nullptr);
    void reSetPoints(QPoint& pt1, QPoint& pt2);
    int pointsXDistance(QPoint& pt1, QPoint& pt2);
    int pointsYDistance(QPoint& pt1, QPoint& pt2);
    void drawRect(QPainter& painter, QPoint& pt1, QPoint& pt2);
    void drawRect(QPainter& painter, int startX, int startY, QRect rc);
    void drawRect(QPainter& painter, int startX, int startY, QPoint center, int width, int height);
    void drawPixmap(QPainter& painter, int startX, int startY, QRect rc, QPixmap& pix);
    void drawPixmap(QPainter& painter, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    void drawPixmap(QPainter& painter, double angle, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    void drawLine(QPainter& painter, int startX, int startY, QPoint pt1, QPoint pt2);
    void drawStraightLine(QPainter& painter, QPoint& pt1, QPoint pt2);
    QPoint getStraightLineEndPoint(QPoint& pt1, QPoint pt2);
    QPoint getTwoPointsCenter(QPoint& pt1, QPoint pt2);
    int getTwoPointsDistance(QPoint& pt1, QPoint pt2);
    bool rectContainsPoint(int startX, int startY, QRect& rc, QPoint& pt);
    int rectAreaSize(QRect& rect);
    void resetRect(QRect& rc, QPoint center, int width, int height);
    double radianToAngle(double d);
    double angleToRadian(double d);


signals:

private:



};

#endif // DRAWOBJECT_H
