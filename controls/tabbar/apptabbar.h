#ifndef APPTABBAR_H
#define APPTABBAR_H

#include <QWidget>
#include <QPainter>
#include <QList>
#include "tabbaritem.h"
#include "../base/widgethelper.h"

namespace Ui
{
class AppTabBar;
}

class AppTabBar : public QWidget
{
    Q_OBJECT

public:
    explicit AppTabBar(QWidget* parent = nullptr);
    ~AppTabBar();
    void addItem(QString caption, QString iconPath);
    void addItem(QString caption, QPixmap selectIcon, QPixmap defaultIcon);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);
    int currentIndex() const;
    void setCurrentIndex(int newCurrentIndex);

signals:
    void clickItem(TabBarItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

private:
    Ui::AppTabBar* ui;
    QList<TabBarItem*> m_items;
    QColor m_backgroundColor;
    WidgetHelper* m_helper;
    int m_currentIndex;
};

#endif // APPTABBAR_H

