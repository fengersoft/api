#include "artpainter.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qpainterpath.h"
#include "qpoint.h"
#include "qrandom.h"
#include "qwindowdefs.h"
#include <cmath>

ArtPainter::ArtPainter(QWidget* parent)
    : QWidget{parent}
{
    m_canvasWidth = 1920;
    m_canvasHeight = 1080;
    m_skyLineValue = 0.6;
    m_skyColors << QColor(84, 133, 252) << QColor(206, 183, 225)
                << QColor(0, 0, 0) << QColor(104, 173, 235) << QColor(95, 106, 128);
    m_skyColorIndex = 0;
    m_skyColor = m_skyColors.at(0);


    m_groundColors << QColor(133, 160, 64) << QColor(204, 192, 235)
                   << QColor(109, 90, 74) << QColor(207, 168, 29)
                   << QColor(6, 5, 8);
    m_groundColorIndex = 0;
    m_groundColor = m_groundColors.at(0);

    m_sunColors << QColor(255, 255, 255) << QColor(223, 223, 242)
                << QColor(255, 255, 255) << QColor(255, 255, 255)
                << QColor(255, 255, 255);
    m_sunColorIndex = 0;
    m_sunColor = m_sunColors.at(0);


    m_hillColors << QColor(133, 160, 64) << QColor(204, 192, 235)
                 << QColor(109, 90, 74) << QColor(207, 168, 29)
                 << QColor(6, 5, 8);
    m_hillColorIndex = 0;
    m_hillColor = m_hillColors.at(0);


    m_linearStyle = true;
    m_sunCenter = QPoint(300, 200);


}

void ArtPainter::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    QRect drawRc(0, 0, m_canvasWidth, m_canvasHeight);
    painter.begin(this);
    QRect skyRc, groundRc, sunRc;
    drawSky(drawRc, painter, skyRc);
    drawGround(drawRc, painter, groundRc);
    drawSun(drawRc, painter, groundRc);
    drawHills(drawRc, painter, groundRc);

    painter.end();

}

void ArtPainter::randomPaint()
{

    m_sunCenter.setX(QRandomGenerator::global()->bounded(200, m_canvasWidth - 200));
//    int linearIndex = QRandomGenerator::global()->bounded(0, 2);

//    m_linearStyle = linearIndex == 0 ? false : true;

    m_skyLineValue = QRandomGenerator::global()->bounded(4, 8) * 0.1;
    int baseIndex = QRandomGenerator::global()->bounded(0, m_skyColors.count());
    m_skyColor = m_skyColors[baseIndex];
    m_groundColor = m_groundColors[baseIndex];
    m_sunColor = m_sunColors[baseIndex];
    m_hillColor = m_hillColors[baseIndex];
    update();

}

void ArtPainter::drawSky(QRect drawRc, QPainter& painter, QRect& resultRc)
{
    painter.save();
    resultRc = QRect(0, 0, drawRc.width(), trunc(drawRc.height() * m_skyLineValue));

    if (m_linearStyle)
    {
        QLinearGradient linearBr;
        linearBr.setStart(0, 0);
        linearBr.setFinalStop(0, resultRc.height());
        linearBr.setColorAt(0, m_skyColor);
        linearBr.setColorAt(1, Qt::white);
        painter.fillRect(resultRc, QBrush(linearBr));
    }
    else
    {
        painter.fillRect(resultRc, QBrush(m_skyColor));
    }


    painter.restore();

}

void ArtPainter::drawGround(QRect drawRc, QPainter& painter, QRect& resultRc)
{
    painter.save();
    int t = trunc(drawRc.height() * m_skyLineValue);
    resultRc = QRect(0, t, drawRc.width(), drawRc.height() - t);

    if (m_linearStyle)
    {
        QLinearGradient linearBr;
        linearBr.setStart(0, t);
        linearBr.setFinalStop(0, t + resultRc.height());

        linearBr.setColorAt(0, Qt::white);
        linearBr.setColorAt(1, m_groundColor);
        painter.fillRect(resultRc, QBrush(linearBr));
    }
    else
    {
        painter.fillRect(resultRc, QBrush(m_groundColor));
    }


    painter.restore();

}

void ArtPainter::drawSun(QRect drawRc, QPainter& painter, QRect& resultRc)
{
    painter.save();
    painter.setBrush(m_sunColor);
    painter.setPen(QColor(203, 203, 203));
    resultRc = QRect(m_sunCenter.x() - 100, m_sunCenter.y() - 100, 100, 100);
    painter.drawEllipse(resultRc);
    painter.restore();


}

void ArtPainter::drawHills(QRect drawRc, QPainter& painter, QRect& resultRc)
{
    int t = trunc(drawRc.height() * m_skyLineValue);
    for (int i = 0; i < 3; i++)
    {
        int x1 = QRandomGenerator::global()->bounded(0, m_canvasWidth);
        int x2 = x1 + QRandomGenerator::global()->bounded(0, m_canvasWidth);
        int m = QRandomGenerator::global()->bounded(x1, x2);
        int h = t * QRandomGenerator::global()->bounded(2, 4) * 0.1;

        drawHill(painter, t, x1, x2, h, m);
    }

}

void ArtPainter::drawHill(QPainter& painter, int bottom, int x, int y, int height, int mid)
{

    qDebug() << bottom << x << y << height << mid;
    painter.save();
    QPainterPath path;
    path.moveTo(QPoint(x, bottom));

    QPoint heightPt(mid, bottom - height);
    QPoint leftPt1((mid + x) / 2, bottom);
    QPoint leftPt2((mid + x) / 2, bottom - height);
    path.cubicTo(leftPt1, leftPt2, heightPt);



    QPoint rightPt(y, bottom);
    QPoint pt4((y + mid) / 2, bottom - height);
    QPoint pt5((y + mid) / 2, bottom);
    path.cubicTo(pt4, pt5, rightPt);



    QLinearGradient linearBr;
    linearBr.setStart(0, bottom - height);
    linearBr.setFinalStop(0, bottom);

    linearBr.setColorAt(0, m_hillColor);

    linearBr.setColorAt(1, QColor(255, 255, 255, 30));
    painter.fillPath(path, linearBr);
    //painter.drawPath(path);
    painter.restore();

}

int ArtPainter::canvasHeight() const
{
    return m_canvasHeight;
}

void ArtPainter::setCanvasHeight(int newCanvasHeight)
{
    m_canvasHeight = newCanvasHeight;
}



int ArtPainter::canvasWidth() const
{
    return m_canvasWidth;
}

void ArtPainter::setCanvasWidth(int newCanvasWidth)
{
    m_canvasWidth = newCanvasWidth;
}
