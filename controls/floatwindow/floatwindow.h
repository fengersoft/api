#ifndef FLOATWINDOW_H
#define FLOATWINDOW_H

#include <QWidget>
#include "abstractfloatwindow.h"
#include "../base/baseitem.h"
#include <QPainter>

namespace Ui {
class FloatWindow;
}

class FloatWindow : public AbstractFloatWindow
{
    Q_OBJECT

public:
    explicit FloatWindow(QWidget *parent = nullptr);
    ~FloatWindow();
    const QPixmap &icon() const;
    void setIcon(const QPixmap &newIcon);

    const QList<BaseItem *> &items() const;
    void setItems(const QList<BaseItem *> &newItems);
    void addItem(QString caption);
signals:
    void clickItem(BaseItem *item);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    Ui::FloatWindow *ui;
    QPixmap m_icon;
    QList<BaseItem*> m_items;
};

#endif // FLOATWINDOW_H
