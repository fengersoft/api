#ifndef SEGMENTBUTTON_H
#define SEGMENTBUTTON_H

#include <QWidget>
#include <QPainter>
#include "../api/draw/drawobject.h"
#include "../api/controls/base/widgethelper.h"
#include "buttonitem.h"

namespace Ui
{
class SegmentButton;
}

class SegmentButton : public QWidget
{
    Q_OBJECT

public:
    explicit SegmentButton(QWidget* parent = nullptr);
    ~SegmentButton();
    void addButton(QString caption);
    ButtonItem* item(int index);
signals:
    void clickItem(ButtonItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::SegmentButton* ui;
    QList<ButtonItem*> m_items;
    DrawObject* m_drawObj;
    WidgetHelper* m_helper;
};

#endif // SEGMENTBUTTON_H
