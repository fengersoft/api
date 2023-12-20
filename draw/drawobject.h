#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include <QObject>
#include <QPainter>
#include <math.h>
#include <QtMath>
#include <QDebug>
#include <QPainterPath>
enum DrawObjectRectStyle
{
    DrawLeft,
    DrawRight,
    DrawNone
};
enum DrawTriangleStyle
{
    DrawTriUp,
    DrawTriDown,
    DrawTriDownV2,
    DrawTriNone
};

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
    void drawRect(QPainter& painter, QRectF rect, bool drawLeft, bool drawTop, bool drawRight, bool drawBottom);
    void drawRect(QPainter& painter, int startX, int startY, QRect rc);
    void drawRect(QPainter& painter, int startX, int startY, QPoint center, int width, int height);
    void drawPixmap(QPainter& painter, int startX, int startY, QRect rc, QPixmap& pix);
    void drawPixmap(QPainter& painter, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    void drawPixmap(QPainter& painter, double angle, int startX, int startY, QPoint center, int width, int height, QPixmap& pix);
    ///自动适应矩形
    QPixmap drawPixmap(QPainter& painter, QRect rect, QPixmap& pix);
    void drawLine(QPainter& painter, int startX, int startY, QPoint pt1, QPoint pt2);
    void drawLines(QPainter& painter, QVector<QPoint>& points);

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

    //绘制原点坐标系
    void drawOriginCross(QPainter& painter, QPoint& centerPoint, QRect& clientRect);


    ///绘制从左向右黄金螺旋线
    void drawLeftGoldSpiral(QPainter& painter, QPoint startPt, int width);

    ///绘制正方形
    void drawSquare(QPainter& painter, QPoint startPoint, int w);

    ///绘制关闭按钮
    void drawCloseButton(QPainter& painter, QRect rc, QColor color, int margin = 4);

    ///绘制关闭按钮
    void drawBackButton(QPainter& painter, QRect rc, QColor color, int penWidth = 1, int margin = 0);

    ///绘制关闭按钮
    void drawAddButton(QPainter& painter, QRect rc, QColor color, int penWidth = 1, int margin = 8);

    ///绘制圆形按钮
    void drawRoundRect(QPainter& painter, QRect rc, QColor color, DrawObjectRectStyle drawStyle);
    void drawRoundedRect(QPainter& painter, QRect rc, QColor fontColor, QColor borderColor,QColor brushColor,
    bool drawLeftTop,bool drawLeftBottom,bool drawRightTop,bool drawRightBottom,int xRadius,int yRadius);
    //绘制三角形
    void drawTriangleButton(QPainter& painter, QRect rc, QColor color, DrawTriangleStyle drawStyle, int padding);
    // 绘制菱形
    void drawDiamond(QPainter& painter, QColor color, QPoint center, int r);
    void drawDiamondF(QPainter& painter, QColor penColor, QColor brushColor, QPointF center, int hr, int startAngle = 30);
    ///绘制垂直文字
    void drawVerText(QPainter& painter, QRect rc, QString text, int flag);

    void drawRoundedRectWithCaption(QPainter& painter, QString caption, QRect rect,
                                    QColor borderColor, QColor brushColor, QColor penColor
                                    ,bool isCaptionCenter);
signals:

private:



};

#endif // DRAWOBJECT_H
