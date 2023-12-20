#ifndef FUNCTIONLIST_H
#define FUNCTIONLIST_H

#include <QWidget>
#include <QPainter>
#include "../../../list/recommendlist.h"
#include "../../base/widgethelper.h"

namespace Ui
{
class FunctionList;
}

class FunctionList : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionList(QWidget* parent = nullptr);
    ~FunctionList();
    void addItem(QString itemName);
    void showAll();
    void search(QString keyword);

protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void leaveEvent(QEvent* event);
private:
    Ui::FunctionList* ui;
    RecommendList* m_list;
    WidgetHelper* m_helper;
};

#endif // FUNCTIONLIST_H
