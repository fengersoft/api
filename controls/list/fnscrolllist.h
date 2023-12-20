#ifndef FNSCROLLLIST_H
#define FNSCROLLLIST_H

#include <QWidget>
#include <QPainter>
#include "fnlistitem.h"
#include "../base/widgethelper.h"

namespace Ui
{
class FnScrollList;
}

class FnScrollList : public QWidget
{
    Q_OBJECT

public:
    explicit FnScrollList(QWidget* parent = nullptr);
    ~FnScrollList();
    void addItem(QString caption);
    void addItemInHead(QString caption);
    bool existsItem(QString caption);
protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::FnScrollList* ui;
    QList<FnListItem*> m_items;
    WidgetHelper* m_helper;
};

#endif // FNSCROLLLIST_H
