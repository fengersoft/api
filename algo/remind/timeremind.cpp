
#include "timeremind.h"

TimeRemind::TimeRemind(QObject* parent)
    : QObject{parent}
{

}

int TimeRemind::getToTimeItems(QList<ReMindItem*>& selectItems,
                               QDateTime datetime, int beforeMinute, int pastMinute)
{
    for (int i = 0; i < items.count(); i++)
    {
        ReMindItem* item = items.at(i);
        if (item->isToTime(datetime, beforeMinute, pastMinute))
        {
            selectItems << item;
        }
    }


    return selectItems.count();

}

