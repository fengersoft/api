#include "outlineviewitem.h"

OutLineViewItem::OutLineViewItem(QObject *parent)
    : QObject{parent}
{
    m_selected=false;
    m_itemType=ItemCate;

}

OutLineViewItem *OutLineViewItem::parent() const
{
    return m_parent;
}

void OutLineViewItem::setParent(OutLineViewItem *newParent)
{
    m_parent = newParent;
}

void OutLineViewItem::addChild(OutLineViewItem *item)
{
    m_children<<item;

}

void OutLineViewItem::insertChild(OutLineViewItem *item, OutLineViewItem *curItem)
{
    int i=m_children.indexOf(curItem);
    m_children.insert(i+1,item);

}



const QRect &OutLineViewItem::rect() const
{
    return m_rect;
}

void OutLineViewItem::setRect(const QRect &newRect)
{
    m_rect = newRect;
}

int OutLineViewItem::id() const
{
    return m_id;
}

void OutLineViewItem::setId(int newId)
{
    m_id = newId;
}

int OutLineViewItem::pid() const
{
    return m_pid;
}

void OutLineViewItem::setPid(int newPid)
{
    m_pid = newPid;
}

const QString &OutLineViewItem::caption() const
{
    return m_caption;
}

void OutLineViewItem::setCaption(const QString &newCaption)
{
    m_caption = newCaption;
}

const QString &OutLineViewItem::name() const
{
    return m_name;
}

void OutLineViewItem::setName(const QString &newName)
{
    m_name = newName;
}

QList<OutLineViewItem *> &OutLineViewItem::childrenIems()
{
    return m_children;

}

bool OutLineViewItem::selected() const
{
    return m_selected;
}

void OutLineViewItem::setSelected(bool newSelected)
{
    m_selected = newSelected;
}

OutLineViewItemType OutLineViewItem::itemType() const
{
    return m_itemType;
}

void OutLineViewItem::setItemType(OutLineViewItemType newItemType)
{
    m_itemType = newItemType;
}

QStringList OutLineViewItem::childrenItemsText()
{
    QStringList stl;
    getChildrenItemsText(this,stl);
    return stl;

}

const QRect &OutLineViewItem::iconRect() const
{
    return m_iconRect;
}

void OutLineViewItem::setIconRect(const QRect &newIconRect)
{
    m_iconRect = newIconRect;
}

void OutLineViewItem::getChildrenItemsText(OutLineViewItem *pItem, QStringList &stl)
{
    for(int i=0;i<pItem->childrenIems().count();i++)
    {
        OutLineViewItem *item=pItem->childrenIems().at(i);
        stl<<item->name();
        getChildrenItemsText(item,stl);
    }

}
