#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <QObject>
#include <QPainter>
#include <math.h>
#include <QtMath>
#include <QDebug>
class DrawObject : public QObject
{
    Q_OBJECT
public:
    explicit DrawObject(QObject* parent = nullptr);
    void reSetPoints(QPoint& pt1, QPoint& pt2);
    int pointsXDistance(QPoint& pt1, QPoint& pt2);
    int pointsYDistance(QPoint& pt1, QPoint& pt2);
    int distance(QPoint pt1, QPoint pt2);
    double distanced(QPoint pt1, QPoint pt2);
    void drawRect(QPainter& painter, QPoint& pt1, QPoint& pt2);
    void drawRect(QPainter& painter, int startX, int startY, QRect rc);
    void drawRect(QPainter& painter, int startX, int startY, QPoint center, int width, int height);
    void drawPixmap(QPainter& painter, int startX, int startY, QRect rc, QPixmap& pix);
    void drawPixmap(QPainter& painter, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    void drawPixmap(QPainter& painter, double angle, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    void drawLine(QPainter& painter, int startX, int startY, QPoint pt1, QPoint pt2);
    bool pointInLine(QPoint pt1, QPoint pt2, QPoint pt);
    void drawStraightLine(QPainter& painter, QPoint& pt1, QPoint pt2);
    QPoint getStraightLineEndPoint(QPoint& pt1, QPoint pt2);
    QPoint getTwoPointsCenter(QPoint& pt1, QPoint pt2);

    bool rectContainsPoint(int startX, int startY, QRect& rc, QPoint& pt);
    bool pointInLine(int startX, int startY, QPoint pt1, QPoint pt2, QPoint& pt);
    bool pointInLined(int startX, int startY, QPoint pt1, QPoint pt2, QPoint& pt);
    int rectAreaSize(QRect& rect);
    void resetRect(QRect& rc, QPoint center, int width, int height);
    double radianToAngle(double d);
    double angleToRadian(double d);
    QRect getRect(QPoint pt1, QPoint pt2);
    double getLineRadian(QPoint pt1, QPoint pt2);
    double getLineAngle(QPoint pt1, QPoint pt2);


signals:

private:



};

#endif // DRAWOBJECT_H
