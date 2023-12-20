#ifndef FNYEARCALENDAR_H
#define FNYEARCALENDAR_H

#include <QWidget>
#include <QDate>
#include <QPainter>
#include <QWheelEvent>
#include <functional>
#include "fncalenderbase.h"
#include "../api/controls/base/widgethelper.h"

namespace Ui
{
class FnYearCalendar;
}

class FnYearCalendar : public QWidget
{
    Q_OBJECT

public:
    explicit FnYearCalendar(QWidget* parent = nullptr);
    ~FnYearCalendar();

    int year() const;
    void setYear(int newYear);
    void initDates();
    float factor() const;
    void setFactor(float newFactor);
    void updateCellData(std::function<void(FnCalenderData*)> updateEvent);
signals:
    void cellClick(FnCalenderData* cell);
    void cellDoubleClick(FnCalenderData* cell);

protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
private:
    Ui::FnYearCalendar* ui;
    int m_year;
    QList<FnCalenderData*> m_items;
    float m_factor;
    double m_cellWidth;
    double m_cellHeight;
    WidgetHelper* m_helper;
    int m_left;
    int m_top;
};

#endif // FNYEARCALENDAR_H
