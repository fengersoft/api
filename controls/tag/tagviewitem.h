#ifndef TAGVIEWITEM_H
#define TAGVIEWITEM_H

#include <QObject>
#include "../base/baseitem.h"

class TagViewItem : public BaseItem
{
    Q_OBJECT
public:
    explicit TagViewItem(QObject* parent = nullptr);

signals:

};

#endif // TAGVIEWITEM_H
