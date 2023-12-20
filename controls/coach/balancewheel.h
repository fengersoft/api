#ifndef BALANCEWHEEL_H
#define BALANCEWHEEL_H

#include <QWidget>
#include <QPainter>
#include "coachingtool.h"
#include "../api/controls/base/widgethelper.h"
#include <QPainterPath>
#include <math.h>
#include "balancewheelitem.h"
#include "editbalancewheelitemdialog.h"

namespace Ui
{
class BalanceWheel;
}

class BalanceWheel : public CoachingTool
{
    Q_OBJECT

public:
    explicit BalanceWheel(QWidget* parent = nullptr);
    ~BalanceWheel();
    double getCurAndle();
    BalanceWheelItem* item(int i);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
private:
    Ui::BalanceWheel* ui;
    QPoint m_center;
    int m_radius;
    BalanceWheelItem* items[8];



};

#endif // BALANCEWHEEL_H
