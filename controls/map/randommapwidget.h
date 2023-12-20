#ifndef RANDOMMAPWIDGET_H
#define RANDOMMAPWIDGET_H

#include <QWidget>
#include "randommappoint.h"
#include <QRandomGenerator64>
#include <QPainter>
#include "randommappointdistance.h"
#include "../../draw/drawobject.h"


namespace Ui {
class RandomMapWidget;
}

class RandomMapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RandomMapWidget(QWidget *parent = nullptr);
    ~RandomMapWidget();
    void createMap();
    void getPointPoints(RandomMapPoint* center);
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::RandomMapWidget *ui;
    QList<RandomMapPoint*> m_mapPoints;
    QList<RandomMapPointDistance*> m_pointDistances;
    DrawObject *m_draw;
};

#endif // RANDOMMAPWIDGET_H
