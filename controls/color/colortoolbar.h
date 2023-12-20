#ifndef COLORTOOLBAR_H
#define COLORTOOLBAR_H

#include "qcolor.h"
#include <QWidget>
#include "colortoolbarbutton.h"
#include <QPainter>
#include "../base/widgethelper.h"
#include "qlist.h"
#include "qobjectdefs.h"

namespace Ui
{
class ColorToolbar;
}

class ColorToolbar : public QWidget
{
    Q_OBJECT

public:
    explicit ColorToolbar(QWidget* parent = nullptr);
    ~ColorToolbar();

    const QColor& backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);

    int selectedIndex() const;
    void setSelectedIndex(int newSelectedIndex);
    void addDefaultColorButtons();
    void addColor(QColor color);
    QColor selectColor();
signals:
    void clickToolbarButton(ColorToolbarButton* btn);
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
private:
    Ui::ColorToolbar* ui;
    QColor m_backgroundColor;
    int m_selectedIndex;
    WidgetHelper* m_helper;
    QList<ColorToolbarButton*> m_buttons;
};

#endif // COLORTOOLBAR_H
