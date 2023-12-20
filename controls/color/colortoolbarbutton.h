#ifndef COLORTOOLBARBUTTON_H
#define COLORTOOLBARBUTTON_H

#include "qcolor.h"
#include <QObject>
#include <QRect>

class ColorToolbarButton : public QObject
{
    Q_OBJECT
public:
    explicit ColorToolbarButton(QObject* parent = nullptr);

    const QColor& color() const;

    const QRect& rect() const;
    void setRect(const QRect& newRect);

    void setColor(const QColor& newColor);

    bool selected() const;
    void setSelected(bool newSelected);

    int index() const;
    void setIndex(int newIndex);

signals:
private:
    QColor m_color;
    QRect m_rect;
    bool m_selected;
    int m_index;

};

#endif // COLORTOOLBARBUTTON_H
