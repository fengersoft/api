#ifndef ARTPAINTER_H
#define ARTPAINTER_H

#include "qcolor.h"
#include "qlist.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qset.h"
#include <QWidget>
#include <QPainter>
#include <math.h>
#include <QDebug>
#include <QRandomGenerator>

class ArtPainter : public QWidget
{
    Q_OBJECT
public:
    explicit ArtPainter(QWidget* parent = nullptr);
    int canvasWidth() const;
    void setCanvasWidth(int newCanvasWidth);




    int canvasHeight() const;
    void setCanvasHeight(int newCanvasHeight);
    void randomPaint();

    void drawSky(QRect drawRc, QPainter& painter, QRect& resultRc);
    void drawGround(QRect drawRc, QPainter& painter, QRect& resultRc);
    void drawSun(QRect drawRc, QPainter& painter, QRect& resultRc);
    void drawHills(QRect drawRc, QPainter& painter, QRect& resultRc);
    void drawHill(QPainter& painter, int bottom, int x, int y, int height, int mid);
protected:
    void paintEvent(QPaintEvent* event);

signals:
private:
    int m_canvasWidth;
    int m_canvasHeight;
    double m_skyLineValue;
    QList<QColor> m_skyColors;
    QColor m_skyColor;
    int m_skyColorIndex;


    QList<QColor> m_groundColors;
    QColor m_groundColor;
    int m_groundColorIndex;

    QList<QColor> m_sunColors;
    QColor m_sunColor;
    int m_sunColorIndex;

    QList<QColor> m_hillColors;
    QColor m_hillColor;
    int m_hillColorIndex;



    bool m_linearStyle;
    QPoint m_sunCenter;

};

#endif // ARTPAINTER_H
