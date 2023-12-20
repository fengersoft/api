#include "colortoolbarbutton.h"

ColorToolbarButton::ColorToolbarButton(QObject* parent)
    : QObject{parent}
{
    m_selected = false;

}

const QColor& ColorToolbarButton::color() const
{
    return m_color;
}

const QRect& ColorToolbarButton::rect() const
{
    return m_rect;
}

void ColorToolbarButton::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

void ColorToolbarButton::setColor(const QColor& newColor)
{
    m_color = newColor;
}

bool ColorToolbarButton::selected() const
{
    return m_selected;
}

void ColorToolbarButton::setSelected(bool newSelected)
{
    m_selected = newSelected;
}

int ColorToolbarButton::index() const
{
    return m_index;
}

void ColorToolbarButton::setIndex(int newIndex)
{
    m_index = newIndex;
}
