
#ifndef TIMEREMIND_H
#define TIMEREMIND_H


#include <QObject>
#include "reminditem.h"


class TimeRemind : public QObject
{
    Q_OBJECT
public:
    explicit TimeRemind(QObject* parent = nullptr);
    QList<ReMindItem*> items;
    int getToTimeItems(QList<ReMindItem*>& selectItems, QDateTime dateTime,
                       int beforeMinute = 10, int pastMinute = 10);
signals:
private:


};

#endif // TIMEREMIND_H
