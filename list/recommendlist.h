#ifndef RECOMMENDLIST_H
#define RECOMMENDLIST_H

#include <QObject>
#include "qdatetime.h"
#include "qlist.h"
#include "qmap.h"
#include "recommendobject.h"

class RecommendList : public QObject
{
    Q_OBJECT
public:
    explicit RecommendList(QObject* parent = nullptr);


    const QList<RecommendObject*>& items() const;
    void setItems(const QList<RecommendObject*>& newItems);
    void addItem(QString name, int selectedCount = 0, QDateTime latestSelectedTime = QDateTime());
    void selectItem(QString name);
    QList<RecommendObject*> showList;
    void showAll();
    void search(QString keyword);
    void smartByReSetOrder();

signals:
private:
    QList<RecommendObject*> m_items;
    QMap<QString, RecommendObject*> m_itemsIndex;

};

#endif // RECOMMENDLIST_H
