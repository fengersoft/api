#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include <QObject>
#include "../base/baseitem.h"

class ButtonItem : public BaseItem
{
    Q_OBJECT
public:
    explicit ButtonItem(QObject* parent = nullptr);

signals:

};

#endif // BUTTONITEM_H
