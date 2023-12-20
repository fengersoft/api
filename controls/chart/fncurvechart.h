#ifndef FNCURVECHART_H
#define FNCURVECHART_H

#include <QWidget>
#include <QPainter>
#include "fnchartview.h"
#include <QPainterPath>
#include "../base/widgethelper.h"

namespace Ui
{
class FnCurveChart;
}

class FnCurveChart : public QWidget
{
    Q_OBJECT

public:
    explicit FnCurveChart(QWidget* parent = nullptr);
    ~FnCurveChart();

    QList<FnChartView*> views() const;
    void setViews(const QList<FnChartView*>& newViews);
    void addView();

    int currentIndex() const;
    void setCurrentIndex(int newCurrentIndex);
    FnChartView* view(int index);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::FnCurveChart* ui;
    QList<FnChartView*> m_views;
    int m_currentIndex;
    WidgetHelper* m_helper;
};

#endif // FNCURVECHART_H
