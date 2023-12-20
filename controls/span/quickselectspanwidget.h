#ifndef QUICKSELECTSPANWIDGET_H
#define QUICKSELECTSPANWIDGET_H

#include "qdatetime.h"
#include <QWidget>
#include <QDate>
#include "spanbutton.h"
#include "../base/widgethelper.h"

namespace Ui
{
class QuickSelectSpanWidget;
}

enum class QuickSelectSpanType
{
    QsDate,
    QsTime
};

class QuickSelectSpanWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QuickSelectSpanWidget(QWidget* parent = nullptr);
    ~QuickSelectSpanWidget();

    const QDate& startDate() const;
    void setStartDate(const QDate& newStartDate);

    const QDate& endDate() const;
    void setEndDate(const QDate& newEndDate);
    void addButtons();
    void calSpan(QString caption, bool bDblClick = false);
    QuickSelectSpanType spanType() const;
    void setSpanType(QuickSelectSpanType newSpanType);
    void afterMinutes(int minutes);

signals:
    void clickSpanButton(QString caption, QDate startDate, QDate endDate);
    void clickSpanTimeButton(QString caption, QDateTime startDate, QDateTime endDate, int minutes);
    void doubleClickSpanButton(QString caption, QDate startDate, QDate endDate);
    void doubleClickSpanTimeButton(QString caption, QDateTime startDate, QDateTime endDate, int minutes);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    Ui::QuickSelectSpanWidget* ui;

private:
    QDate m_startDate;
    QDate m_endDate;
    QDateTime m_startDateTime;
    QDateTime m_endDateTime;
    QList<SpanButton*> m_buttons;
    WidgetHelper* m_helper;
    QuickSelectSpanType m_spanType;
    int m_afterMinutes;
};

#endif // QUICKSELECTSPANWIDGET_H
