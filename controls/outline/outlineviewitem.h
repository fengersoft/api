#ifndef OUTLINEVIEWITEM_H
#define OUTLINEVIEWITEM_H

#include <QObject>
#include <QRect>
#include <QColor>

enum OutLineViewItemType
{
    ItemCate,
    ItemInfo
};

class OutLineViewItem : public QObject
{
    Q_OBJECT
public:
    explicit OutLineViewItem(QObject *parent = nullptr);

    OutLineViewItem *parent() const;
    void setParent(OutLineViewItem *newParent);
    void addChild(OutLineViewItem *item);
    void insertChild(OutLineViewItem *item,OutLineViewItem *curItem);

    const QRect &rect() const;
    void setRect(const QRect &newRect);

    int id() const;
    void setId(int newId);

    int pid() const;
    void setPid(int newPid);

    const QString &caption() const;
    void setCaption(const QString &newCaption);

    const QString &name() const;
    void setName(const QString &newName);
    QList<OutLineViewItem*>& childrenIems();

    bool selected() const;
    void setSelected(bool newSelected);

    OutLineViewItemType itemType() const;
    void setItemType(OutLineViewItemType newItemType);
    QStringList childrenItemsText();

    const QRect &iconRect() const;
    void setIconRect(const QRect &newIconRect);

signals:
private:
    OutLineViewItem* m_parent;
    QList<OutLineViewItem*> m_children;
    QRect m_rect;
    QString m_caption;
    QString m_name;
    int m_id;
    int m_pid;
    bool m_selected;
    OutLineViewItemType m_itemType;
    QRect m_iconRect;
    void getChildrenItemsText(OutLineViewItem *pItem,QStringList &stl);

};

#endif // OUTLINEVIEWITEM_H
