#include "randommapwidget.h"
#include "ui_randommapwidget.h"

RandomMapWidget::RandomMapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RandomMapWidget)
{
    ui->setupUi(this);
    m_draw=new DrawObject(this);
}

RandomMapWidget::~RandomMapWidget()
{
    delete ui;
}

void RandomMapWidget::createMap()
{


    int r=4;
    double l;
    double t=r*2;
    for(int i=0;i<100;i++)
    {
        if (i%2==0)
        {
          l=r*2;
        }else
        {
            l=r*2+sqrt(3)*r;
        }

        for (int j=0;j<100;j++)
        {
            RandomMapPoint *pt=new RandomMapPoint();
            pt->setCenterX(l);
            pt->setCenterY(t);

            m_mapPoints<<pt;
            l+=2*sqrt(3)*r;
        }
        t+=r*3;
    }

    update();

}

void RandomMapWidget::getPointPoints(RandomMapPoint *center)
{
    QList<RandomMapPoint*> tempPoints;

}

void RandomMapWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    for(int i=0;i<m_mapPoints.count();i++)
    {
        RandomMapPoint *pt=m_mapPoints.at(i);


        QColor br(QRandomGenerator64::global()->bounded(0,256),
                  QRandomGenerator64::global()->bounded(0,256),
                  QRandomGenerator64::global()->bounded(0,256));
        m_draw->drawDiamondF(painter,Qt::NoPen,br,QPointF(pt->centerX(),pt->centerY()),4);


    }

    painter.end();

}
