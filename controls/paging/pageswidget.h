#ifndef PAGESWIDGET_H
#define PAGESWIDGET_H

#include "qlist.h"
#include <QWidget>
#include "pagebutton.h"
#include <QPainter>
#include <QWheelEvent>
#include "../base/widgethelper.h"
#include "qtmetamacros.h"

namespace Ui
{
class pagesWidget;
}

class pagesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit pagesWidget(QWidget* parent = nullptr);
    ~pagesWidget();

    int pageCount() const;
    void setPageCount(int newPageCount);
signals:
    void getPageNum(int pageNum);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::pagesWidget* ui;
    int m_pageCount;
    QList<PageButton*> m_buttons;
    WidgetHelper* m_helper;
};

#endif // PAGESWIDGET_H
