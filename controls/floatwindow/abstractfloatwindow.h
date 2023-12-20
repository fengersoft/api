#ifndef ABSTRACTFLOATWINDOW_H
#define ABSTRACTFLOATWINDOW_H

#include <QWidget>
#include <QAction>
#include "../base/widgethelper.h"

class AbstractFloatWindow : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractFloatWindow(QWidget *parent = nullptr);
protected:
     void mousePressEvent(QMouseEvent *event);
     void mouseReleaseEvent(QMouseEvent *event);
     void mouseDoubleClickEvent(QMouseEvent *event);
     void mouseMoveEvent(QMouseEvent *event);
     WidgetHelper *m_helper;
signals:
public slots:
     void onTriggered();
};

#endif // ABSTRACTFLOATWINDOW_H
