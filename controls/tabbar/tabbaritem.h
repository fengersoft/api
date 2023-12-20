#ifndef TABBARITEM_H
#define TABBARITEM_H

#include <QObject>
#include <QPixmap>

class TabBarItem : public QObject
{
    Q_OBJECT
public:
    explicit TabBarItem(QObject* parent = nullptr);

    QPixmap icon() const;
    void setIcon(const QPixmap& newIcon);

    QPixmap selectedIcon() const;

    QString capiton() const;
    void setCapiton(const QString& newCapiton);

    void setSelectedIcon(const QPixmap& newSelectedIcon);

    bool isSelected() const;
    void setIsSelected(bool newIsSelected);

    QRect rect() const;

    QColor textColor() const;
    void setTextColor(const QColor& newTextColor);

    QColor textSelectedColor() const;
    void setTextSelectedColor(const QColor& newTextSelectedColor);

    void setRect(const QRect& newRect);

    int index() const;
    void setIndex(int newIndex);

signals:
private:
    QString m_capiton;
    QPixmap m_icon;
    QPixmap m_selectedIcon;
    bool m_isSelected;
    QRect m_rect;
    QColor m_textColor;
    QColor m_textSelectedColor;
    int m_index;

};

#endif // TABBARITEM_H
