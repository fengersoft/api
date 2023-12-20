#include "drawobject.h"
#include "qpixmap.h"

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

int DrawObject::distance(QPoint pt1, QPoint pt2)
{

    int n = sqrt((pt1.x() - pt2.x()) * (pt1.x() - pt2.x()) + (pt1.y() - pt2.y()) * (pt1.y() - pt2.y()));

    return n;
}

double DrawObject::distanced(QPoint pt1, QPoint pt2)
{
    double n = sqrt((pt1.x() - pt2.x()) * (pt1.x() - pt2.x()) + (pt1.y() - pt2.y()) * (pt1.y() - pt2.y()));

    return n;
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

void DrawObject::drawRect(QPainter& painter, QRectF rect, bool drawLeft, bool drawTop, bool drawRight, bool drawBottom)
{
    if (drawLeft)
    {
        painter.drawLine(rect.left(), rect.top(), rect.left(), rect.bottom());
    }
    if (drawTop)
    {
        painter.drawLine(rect.left(), rect.top(), rect.right(), rect.top());
    }
    if (drawRight)
    {
        painter.drawLine(rect.right(), rect.top(), rect.right(), rect.bottom());
    }


    if (drawBottom)
    {
        painter.drawLine(rect.left(), rect.top() + rect.height(), rect.right(), rect.top() + rect.height());
        qDebug() << (rect.top() + rect.height());
    }


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

QPixmap DrawObject::drawPixmap(QPainter& painter, QRect rect, QPixmap& pix)
{
    double f1 = (double)rect.width();
    f1 = f1 / rect.height();
    double f2 = (double)pix.width();
    f2 = f2 / pix.height();
    QPixmap temp;
    QRect drawRc;
    if (f1 >= f2)
    {
        //等高
        temp = pix.scaledToHeight(rect.height(), Qt::SmoothTransformation);
        int l = rect.left() + (rect.width() - temp.width()) / 2;
        drawRc = QRect(l, rect.top(), temp.width(), temp.height());

    }
    else
    {
        temp = pix.scaledToWidth(rect.width(), Qt::SmoothTransformation);
        int t = rect.top() + (rect.height() - temp.height()) / 2;
        drawRc = QRect(rect.left(), t, temp.width(), temp.height());
    }
    painter.drawPixmap(drawRc, temp, temp.rect());
    return temp;

}

void DrawObject::drawLine(QPainter& painter, int startX, int startY, QPoint pt1, QPoint pt2)
{
    QPoint p1 = QPoint(pt1.x() + startX, pt1.y() + startY);
    QPoint p2 = QPoint(pt2.x() + startX, pt2.y() + startY);
    painter.drawLine(p1, p2);

}

void DrawObject::drawLines(QPainter& painter, QVector<QPoint>& points)
{
    QPoint pt1, pt2, pt0;
    for (int i = 0; i < points.count(); i++)
    {
        if (i == 0)
        {
            pt1 = points.at(i);
            pt0 = points.at(i);
            pt2 = pt1;
        }
        else
        {
            pt2 = points.at(i);
            painter.drawLine(pt1.x(), pt1.y(), pt2.x(), pt2.y());
            pt1 = pt2;
        }
    }


}

bool DrawObject::pointInLine(QPoint pt1, QPoint pt2, QPoint pt)
{

    if ((distance(pt1, pt) + distance(pt2, pt)) == distance(pt1, pt2))
    {
        return true;
    }
    else
    {
        return false;
    }
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



bool DrawObject::rectContainsPoint(int startX, int startY, QRect& rc, QPoint& pt)
{
    QRect newRc = QRect(rc.left() + startX, rc.top() + startY, rc.width(), rc.height());
    return newRc.contains(pt);
}

bool DrawObject::pointInLine(int startX, int startY, QPoint pt1, QPoint pt2, QPoint& pt)
{
    QPoint p1 = QPoint(pt1.x() + startX, pt1.y() + startY);
    QPoint p2 = QPoint(pt2.x() + startX, pt2.y() + startY);
    if (abs(distance(p1, pt) + distance(p2, pt) - distance(p1, p2)) <= 1)
    {

        return true;
    }
    else
    {
        return false;
    }
}

bool DrawObject::pointInLined(int startX, int startY, QPoint pt1, QPoint pt2, QPoint& pt)
{
    QPoint p1 = QPoint(pt1.x() + startX, pt1.y() + startY);
    QPoint p2 = QPoint(pt2.x() + startX, pt2.y() + startY);
    if (abs(distanced(p1, pt) + distanced(p2, pt) - distanced(p1, p2)) <= 0.05)
    {

        return true;
    }
    else
    {
        return false;
    }
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

QRect DrawObject::getRect(QPoint pt1, QPoint pt2)
{
    return QRect(pt1.x(), pt1.y(), abs(pt1.x() - pt2.x()), abs(pt1.y() - pt2.y()));
}

double DrawObject::getLineRadian(QPoint pt1, QPoint pt2)
{
    return atan2(pt2.y() - pt1.y(), pt2.x() - pt1.x());
}

double DrawObject::getLineAngle(QPoint pt1, QPoint pt2)
{
    return atan2(pt2.y() - pt1.y(), pt2.x() - pt1.x()) * (180 / 3.141592653);
}

void DrawObject::drawOriginCross(QPainter& painter, QPoint& centerPoint, QRect& clientRect)
{
    painter.drawLine(clientRect.left(), centerPoint.y(), clientRect.right(), centerPoint.y());
    painter.drawLine(centerPoint.x(), clientRect.top(), centerPoint.x(), clientRect.bottom());
}

void DrawObject::drawLeftGoldSpiral(QPainter& painter, QPoint startPt, int width)
{
    double f1 = 0.618;

    int ws[9];
    int xpos[9];
    int ypos[9];
    int w = width;
    bool f = true;
    for (int i = 0; i < 9; i++)
    {
//        if (i == 0)
//        {
//            ws[i] = w * f1;
//        }
//        else if (i == 1)
//        {
//            ws[i] = w - ws[0];
//        }
//        else
//        {
//            ws[i] = ws[i - 2] - ws[i - 1];
//        }


        if (f == true)
        {
            ws[i] = w * f1;
        }
        else
        {
            ws[i] = w - ws[i - 1];
            w =  ws[i];
        }



        f = !f;
    }
    int x = startPt.x();
    int y = startPt.y();
    int i = 0;
    xpos[i] = x;
    ypos[i] = y;
    drawSquare(painter, QPoint(x, y), ws[i]);

    i++;
    x += ws[i - 1];
    xpos[i] = x - ws[i];
    ypos[i] = y;
    drawSquare(painter, QPoint(x, y), ws[i]);

    i++;
    x = x + ws[i - 1] - ws[i];
    y += ws[i - 1];
    xpos[i] = x - ws[i];
    ypos[i] = y - ws[i];
    drawSquare(painter, QPoint(x, y), ws[i]);

    i++;
    x = x  - ws[i];
    y = y + ws[i - 1] - ws[i];
    xpos[i] = x ;
    ypos[i] = y - ws[i];
    drawSquare(painter, QPoint(x, y), ws[i]);

    i++;
    y = y - ws[i];
    xpos[i] = x;
    ypos[i] = y;
    drawSquare(painter, QPoint(x, y), ws[i]);


    i++;

    x = x + ws[i - 1];
    xpos[i] = x - ws[i];
    ypos[i] = y;
    drawSquare(painter, QPoint(x, y), ws[i]);

    i++;
    y = y + ws[i - 1];
    x = x + ws[i - 1] - ws[i];
    xpos[i] = x - ws[i];
    ypos[i] = y - ws[i];
    drawSquare(painter, QPoint(x, y), ws[i]);

    i++;
    y = y + ws[i - 1] - ws[i];
    x = x - ws[i];
    xpos[i] = x ;
    ypos[i] = y - ws[i];
    drawSquare(painter, QPoint(x, y), ws[i]);


    int n = 90;
    for (int i = 0; i < 9; i++)
    {
        QRect rc(xpos[i], ypos[i], ws[i] * 2, ws[i] * 2);
        painter.drawArc(rc, n * 16, 90 * 16);
        n -= 90;
    }



    qDebug() << "----------------";



//    int h = width * 0.618;
//    QRect rc;
//    painter.drawLine(startPt, QPoint(startPt.x() + width, startPt.y()));
//    painter.drawLine(startPt, QPoint(startPt.x(), startPt.y() + h));
//    painter.drawLine(QPoint(startPt.x(), startPt.y() + h), QPoint(startPt.x() + width, startPt.y() + h));
//    painter.drawLine(QPoint(startPt.x() + width, startPt.y()), QPoint(startPt.x() + width, startPt.y() + h));


//    //竖线
//    painter.drawLine(QPoint(startPt.x() + h, startPt.y()), QPoint(startPt.x() + h, startPt.y() + h));

//    rc = QRect(startPt.x(), startPt.y(), h * 2, h * 2);
//    painter.drawArc(rc, 90 * 16, 90 * 16);


//    int w1 = width - h;

//    painter.drawLine(QPoint(startPt.x() + h, startPt.y() + w1), QPoint(startPt.x() + width, startPt.y() + w1));

//    rc = QRect(startPt.x() + h - w1, startPt.y(), w1 * 2, w1 * 2);
//    painter.drawArc(rc, 0 * 16, 90 * 16);

//    int w2 = w1 - w1 * 0.618;

//    //右侧横线
//    painter.drawLine(QPoint(startPt.x() + h + w2, startPt.y() + w1), QPoint(startPt.x() + h + w2, startPt.y() + h));

//    //绘制第三段曲线
//    int w3 = w1 * 0.618;
//    rc = QRect(startPt.x() + width - w3 * 2, startPt.y() + h - w3 * 2, w3 * 2, w3 * 2);
//    painter.drawArc(rc, 270 * 16, 90 * 16);


//    int h2 = h - (h * 0.618);
//    h2 = h2 - (h2 * 0.618);
//    int h3 = h2 * 0.618;
//    painter.drawLine(QPoint(startPt.x() + h, startPt.y() + w1), QPoint(startPt.x() + h + h3, startPt.y() + w1));





}

void DrawObject::drawSquare(QPainter& painter, QPoint startPoint, int w)
{

    painter.drawLine(startPoint.x(), startPoint.y(),
                     startPoint.x() + w, startPoint.y());
    painter.drawLine(startPoint.x(), startPoint.y() + w,
                     startPoint.x() + w, startPoint.y() + w);

    painter.drawLine(startPoint.x(), startPoint.y(),
                     startPoint.x(), startPoint.y() + w);
    painter.drawLine(startPoint.x() + w, startPoint.y(),
                     startPoint.x() + w, startPoint.y() + w);
}

void DrawObject::drawCloseButton(QPainter& painter, QRect rc, QColor color, int margin)
{
    painter.setPen(color);
    painter.drawLine(rc.left() + margin, rc.top() + margin, rc.right() - margin, rc.bottom() - margin);
    painter.drawLine(rc.right() - margin, rc.top() + margin, rc.left() + margin, rc.bottom() - margin);
}

void DrawObject::drawBackButton(QPainter& painter, QRect rc, QColor color, int penWidth, int margin)
{


    painter.save();
    QPen pen = painter.pen();
    pen.setWidth(penWidth);
    pen.setColor(color);
    painter.setPen(pen);
    painter.drawLine(rc.center().x() - rc.width() / 8, rc.center().y(), rc.center().x() + rc.width() / 4, rc.top() + margin);
    painter.drawLine(rc.center().x() - rc.width() / 8, rc.center().y(), rc.center().x() + rc.width() / 4, rc.bottom() - margin);
    painter.restore();
}

void DrawObject::drawAddButton(QPainter& painter, QRect rc, QColor color, int penWidth, int margin)
{
    painter.save();

    QPen pen = painter.pen();
    pen.setWidth(penWidth);
    pen.setColor(color);
    painter.setPen(pen);
    painter.drawEllipse(rc.center(), rc.width() / 2, rc.height() / 2);
    painter.drawLine(rc.center().x() - rc.width() / 2 + margin, rc.center().y(), rc.center().x() + rc.width() / 2 - margin, rc.center().y());
    painter.drawLine(rc.center().x(), rc.center().y() - rc.width() / 2 + margin, rc.center().x(), rc.center().y() + rc.width() / 2 - margin);
    painter.restore();
}

void DrawObject::drawRoundRect(QPainter& painter, QRect rc, QColor color, DrawObjectRectStyle drawStyle)
{
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    painter.drawRoundedRect(rc, 5, 5);

    if (drawStyle == DrawLeft)
    {

        QRect rc2(rc.center().x() + 1, rc.top(), rc.width() / 2, rc.height());
        painter.drawRect(rc2);
    }
    else if (drawStyle == DrawRight)
    {
        QRect rc2(rc.left(), rc.top(), rc.width() / 2, rc.height());
        painter.drawRect(rc2);
    }
    else
    {
        QRect rc2(rc.left(), rc.top(), rc.width(), rc.height());
        painter.drawRect(rc2);
    }

    painter.restore();

}

void DrawObject::drawRoundedRect(QPainter &painter, QRect rc,  QColor fontColor, QColor borderColor, QColor brushColor, bool drawLeftTop, bool drawLeftBottom, bool drawRightTop, bool drawRightBottom,int xRadius,int yRadius)
{

    if ((drawLeftTop==false) &&
(drawLeftBottom==false) &&
(drawRightTop==false) &&
        (drawRightBottom==false) )
    {
        QRect tmp(rc.left(),rc.top(),rc.width(),rc.height()-1);
        painter.fillRect(tmp,QBrush(brushColor));

    }else
    {
        QRect tmp1(rc.left(),rc.top()+yRadius-1,rc.width(),rc.height()-2*yRadius+2);
        painter.fillRect(tmp1,QBrush(brushColor));

        QRect tmp2(rc.left()+xRadius-1,rc.top(),rc.width()-2*xRadius+2,rc.height()-1);
        painter.fillRect(tmp2,QBrush(brushColor));
    }
    if ((drawRightTop==false) &&
        (drawRightTop==false))
    {
        QRect tmp(rc.right()-xRadius,rc.top(),xRadius+1,rc.height()-1);
        painter.fillRect(tmp,QBrush(brushColor));
    }

    if ((drawLeftTop==false) &&
        (drawLeftBottom==false))
    {
        QRect tmp(rc.left(),rc.top(),xRadius,rc.height()-1);
        painter.fillRect(tmp,QBrush(brushColor));
    }


    if (drawLeftTop)
    {
        painter.setBrush(QBrush(brushColor));
        painter.setPen(Qt::NoPen);
        painter.drawPie(QRect(rc.left(),rc.top(),xRadius*2,yRadius*2),
                        90*16,90*16);
        painter.setPen(borderColor);
        painter.drawArc(QRect(rc.left(),rc.top(),xRadius*2,yRadius*2),
                        90*16,90*16);

    }else
    {
         painter.setPen(borderColor);
        painter.drawLine(rc.left(),rc.top(),rc.left()+xRadius,rc.top());
        painter.drawLine(rc.left(),rc.top(),rc.left(),rc.top()+yRadius);
    }

    //左
     painter.setPen(borderColor);
    painter.drawLine(rc.left(),rc.top()+yRadius,rc.left(),rc.bottom()-yRadius);

    //左下
    if (drawLeftBottom)
    {
        painter.setBrush(QBrush(brushColor));
        painter.setPen(Qt::NoPen);
        painter.drawPie(QRect(rc.left(),rc.bottom()-2*yRadius,xRadius*2,yRadius*2),
                        180*16,90*16);
        painter.setPen(borderColor);
        painter.drawArc(QRect(rc.left(),rc.bottom()-2*yRadius,xRadius*2,yRadius*2),
                        180*16,90*16);
    }else
    {
         painter.setPen(borderColor);
        painter.drawLine(rc.left(),rc.bottom(),rc.left()+xRadius,rc.bottom());
        painter.drawLine(rc.left(),rc.bottom()-yRadius,rc.left(),rc.bottom());
    }
      painter.setPen(borderColor);
     painter.drawLine(rc.left()+xRadius,rc.bottom(),rc.right()-xRadius,rc.bottom());

     //右下

     if (drawRightBottom)
     {
        painter.setBrush(QBrush(brushColor));
        painter.setPen(Qt::NoPen);
        painter.drawPie(QRect(rc.right()-2*xRadius+1,rc.bottom()-2*yRadius,xRadius*2,yRadius*2),
                        270*16,90*16);
        painter.setPen(borderColor);
        painter.drawArc(QRect(rc.right()-2*xRadius+1,rc.bottom()-2*yRadius,xRadius*2,yRadius*2),
                        270*16,90*16);
     }else
     {
         painter.setPen(borderColor);
        painter.drawLine(rc.right()-xRadius,rc.bottom(),rc.right(),rc.bottom());
        painter.drawLine(rc.right()+1,rc.bottom()-yRadius,rc.right()+1,rc.bottom());
     }
     //右边竖线
      painter.setPen(borderColor);
     painter.drawLine(rc.right()+1,rc.top()+yRadius,rc.right()+1,rc.bottom()-yRadius);


     if (drawRightTop)
     {
        painter.setBrush(QBrush(brushColor));
        painter.setPen(Qt::NoPen);
        painter.drawPie(QRect(rc.right()-2*xRadius+1,rc.top(),xRadius*2,yRadius*2),
                        0*16,90*16);
        painter.setPen(borderColor);
        painter.drawArc(QRect(rc.right()-2*xRadius+1,rc.top(),xRadius*2,yRadius*2),
                        0*16,90*16);
     }else
     {
         painter.setPen(borderColor);
        painter.drawLine(rc.right()-xRadius,rc.top(),rc.right(),rc.top());
        painter.drawLine(rc.right()+1,rc.top(),rc.right()+1,rc.top()+yRadius);
     }
      painter.setPen(borderColor);
      painter.drawLine(rc.left()+xRadius,rc.top(),rc.right()-xRadius,rc.top());



}

void DrawObject::drawTriangleButton(QPainter& painter, QRect rc, QColor color, DrawTriangleStyle drawStyle, int padding)
{
    painter.save();
    QPainterPath path;
    double h = ((rc.width() - padding * 2) / 2) * sqrt(3);
    if (drawStyle == DrawTriUp)
    {
        path.moveTo(rc.center().x(), rc.bottom() - padding - h);
        path.lineTo(rc.left() + padding, rc.bottom() - padding);
        path.lineTo(rc.right() - padding, rc.bottom() - padding);
        painter.fillPath(path, QBrush(color));
    }
    else if (drawStyle == DrawTriDownV2)
    {
        path.moveTo(rc.left() + padding, rc.center().y());
        path.lineTo(rc.center().x(), rc.bottom() - padding);
        path.lineTo(rc.right() - padding,  rc.center().y());

        painter.drawPath(path);

    }
    else
    {

        path.moveTo(rc.left() + padding, rc.bottom() - padding - h);
        path.lineTo(rc.right() - padding,  rc.bottom() - padding - h);
        path.lineTo(rc.center().x(), rc.bottom() - padding);
        painter.fillPath(path, QBrush(color));
    }



    painter.restore();

}

void DrawObject::drawDiamond(QPainter& painter, QColor color, QPoint center, int r)
{
    QPolygonF pol;
    for (int i = 0; i < 6; i++)
    {
        QPointF ptf;
        ptf.setX(center.x() + r * cos((i * 60) * (3.1415926 / 180)));
        ptf.setY(center.y() + r * sin((i * 60) * (3.1415926 / 180)));
        pol << ptf;
    }

    painter.drawPolygon(pol);

}



void DrawObject::drawDiamondF(QPainter& painter, QColor penColor, QColor brushColor, QPointF center, int hr, int startAngle)
{
    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(brushColor);
    QPolygonF pol;
    for (int i = 0; i < 6; i++)
    {
        QPointF ptf;
        ptf.setX(center.x() + 2 * hr * cos((i * 60 + startAngle) * (3.1415926 / 180)));
        ptf.setY(center.y() + 2 * hr * sin((i * 60 + startAngle) * (3.1415926 / 180)));
        pol << ptf;
    }

    painter.drawPolygon(pol);
    painter.restore();

}

void DrawObject::drawVerText(QPainter& painter, QRect rc, QString text, int flag)
{
    QFontMetrics fm = painter.fontMetrics();
    int t = rc.top();
    for (int i = 0; i < text.length(); i++)
    {
        QRect textRc(rc.left(), t, rc.width(), fm.height());
        painter.drawText(textRc, Qt::AlignCenter, text.at(i));

        t += fm.height();
    }

}

void DrawObject::drawRoundedRectWithCaption(QPainter& painter, QString caption,
                                            QRect rect,
                                            QColor borderColor, QColor brushColor,
                                            QColor penColor
                                            ,bool isCaptionCenter)
{
    painter.setPen(borderColor);
    painter.setBrush(QBrush(brushColor));
    painter.drawRoundedRect(rect, 16, 16);
    QRect captionRc(rect.left() + 16, rect.top() + 8, rect.width() - 32, 24);
    painter.setPen(penColor);
    if (isCaptionCenter)
    {
        painter.drawText(captionRc, Qt::AlignCenter,caption);
    }else
    {
         painter.drawText(captionRc, caption, Qt::AlignLeft | Qt::AlignVCenter);
    }




}


