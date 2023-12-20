#include "recommendlist.h"
#include "qalgorithms.h"
#include "qlist.h"
#include "recommendobject.h"

RecommendList::RecommendList(QObject* parent)
    : QObject{parent}
{

}

const QList<RecommendObject*>& RecommendList::items() const
{
    return m_items;
}

void RecommendList::setItems(const QList<RecommendObject*>& newItems)
{
    m_items = newItems;
}

void RecommendList::addItem(QString name, int selectedCount, QDateTime latestSelectedTime)
{

    RecommendObject* item = new RecommendObject(this);
    item->setName(name);
    item->setSelectedCount(selectedCount);
    item->setLatestSelectedTime(latestSelectedTime);
    m_items << item;
    m_itemsIndex[name] = item;
}

void RecommendList::selectItem(QString name)
{
    RecommendObject* item = m_itemsIndex.value(name, nullptr);
    if (item == nullptr)
    {
        return;
    }
    item->incSelectedCount();


}

void RecommendList::showAll()
{
    showList.clear();
    showList << m_items;

}

void RecommendList::search(QString keyword)
{
    showList.clear();
    for (RecommendObject* item : qAsConst(m_items))
    {
        if (item->name().indexOf(keyword) >= 0)
        {
            showList << item;
        }
    }


}

void RecommendList::smartByReSetOrder()
{
    qSort(showList.begin(), showList.end(), [](RecommendObject * item1, RecommendObject * item2)
    {
        return item1->latestSelectedTime() > item2->latestSelectedTime();
    });

    if (showList.count() > 3)
    {
        QList<RecommendObject*> tmpList = showList.mid(3);
        qSort(tmpList.begin(), tmpList.end(), [](RecommendObject * item1, RecommendObject * item2)
        {

            return item1->selectedCount() > item2->selectedCount();
        });
        while (showList.count() > 3)
        {
            showList.removeLast();
        }
        showList << tmpList;
    }

}

