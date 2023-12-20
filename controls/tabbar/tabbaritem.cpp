#include "tabbaritem.h"

TabBarItem::TabBarItem(QObject* parent)
    : QObject{parent}
{

}

QPixmap TabBarItem::icon() const
{
    return m_icon;
}

void TabBarItem::setIcon(const QPixmap& newIcon)
{
    m_icon = newIcon;
}

QPixmap TabBarItem::selectedIcon() const
{
    return m_selectedIcon;
}

QString TabBarItem::capiton() const
{
    return m_capiton;
}

void TabBarItem::setCapiton(const QString& newCapiton)
{
    m_capiton = newCapiton;
}

void TabBarItem::setSelectedIcon(const QPixmap& newSelectedIcon)
{
    m_selectedIcon = newSelectedIcon;
}

bool TabBarItem::isSelected() const
{
    return m_isSelected;
}

void TabBarItem::setIsSelected(bool newIsSelected)
{
    m_isSelected = newIsSelected;
}

QRect TabBarItem::rect() const
{
    return m_rect;
}

QColor TabBarItem::textColor() const
{
    return m_textColor;
}

void TabBarItem::setTextColor(const QColor& newTextColor)
{
    m_textColor = newTextColor;
}

QColor TabBarItem::textSelectedColor() const
{
    return m_textSelectedColor;
}

void TabBarItem::setTextSelectedColor(const QColor& newTextSelectedColor)
{
    m_textSelectedColor = newTextSelectedColor;
}

void TabBarItem::setRect(const QRect &newRect)
{
    m_rect = newRect;
}

int TabBarItem::index() const
{
    return m_index;
}

void TabBarItem::setIndex(int newIndex)
{
    m_index = newIndex;
}
