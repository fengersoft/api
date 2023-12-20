#ifndef OFFICESTARTNAVIGATIONBAR_H
#define OFFICESTARTNAVIGATIONBAR_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include "../base/widgethelper.h"
#include "../base/baseitem.h"
#include <QList>

namespace Ui
{
class OfficeStartNavigationBar;
}

class OfficeStartNavigationBar : public QWidget
{
    Q_OBJECT

public:
    explicit OfficeStartNavigationBar(QWidget* parent = nullptr);
    ~OfficeStartNavigationBar();

    const QColor& backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);
    void addIconButton(QString caption, QString imagePath);
    const QColor& selectColor() const;
    void setSelectColor(const QColor& newSelectColor);
    BaseItem* iconButton(int index);

    const QString& caption() const;
    void setCaption(const QString& newCaption);

    const QColor& hotColor() const;
    void setHotColor(const QColor& newHotColor);
    BaseItem* getSelectIconButton();
signals:
    void clickIconButton(BaseItem* item);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::OfficeStartNavigationBar* ui;
    QColor m_backgroundColor;
    QColor m_selectColor;
    QColor m_hotColor;
    WidgetHelper* m_helper;
    QList<BaseItem*> m_iconButtons;
    QList<BaseItem*> m_noIconButtons;
    QString m_caption;
};

#endif // OFFICESTARTNAVIGATIONBAR_H
