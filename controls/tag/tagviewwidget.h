#ifndef TAGVIEWWIDGET_H
#define TAGVIEWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include <QMouseEvent>
#include <QMenu>

#include "../api/color/colortable.h"
#include "tagviewitem.h"
#include "../base/widgethelper.h"

namespace Ui
{
class TagViewWidget;
}

class TagViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TagViewWidget(QWidget* parent = nullptr);
    ~TagViewWidget();
    void addItem(int id, QString caption);
signals:
    void clickItem(TagViewItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::TagViewWidget* ui;
    QList<TagViewItem*> m_items;
    WidgetHelper* m_helper;
};

#endif // TAGVIEWWIDGET_H
