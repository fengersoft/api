#ifndef MAPROADWIDGET_H
#define MAPROADWIDGET_H

#include <QWidget>
#include "maproadpoint.h"
#include "maproadline.h"
#include "../base/widgethelper.h"
#include <QPainter>
#include <QPainterPath>
namespace Ui
{
class MapRoadWidget;
}


class MapRoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapRoadWidget(QWidget* parent = nullptr);
    ~MapRoadWidget();
    void getStartPoint();
    void getEndPoint();
    const QPixmap& backgroundImage() const;
    void setBackgroundImage(const QPixmap& newBackgroundImage);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
private:
    Ui::MapRoadWidget* ui;
    QList<MapRoadPoint*> m_points;
    QList< MapRoadLine* > m_lines;

    WidgetHelper* m_helper;
    MapRoadPoint* m_startPoint;
    QPoint m_movePoint;
    MapRoadPoint* m_endPoint;
    QPixmap m_backgroundImage;

};

#endif // MAPROADWIDGET_H
