#ifndef COUPLELIST_H
#define COUPLELIST_H
#include "couple.h"
#include <QList>
#include <QDebug>
#include <QSet>
template< typename T>
class CoupleList: public QList< Couple<T> >
{
public:
    inline void appendCouple(T t1, T t2)
    {
        Couple<T> t(t1, t2);
        *this << t;

    }
    inline QSet<T> others(T t)
    {
        QSet<T> stl;
        bool f;
        for (int i = 0; i < (*this).count(); i++)
        {
            Couple<T> tt = (*this).at(i);
            T s = tt.other(t, &f);

            if (f)
            {
                stl << s;
            }
        }

        return stl;
    }


};

#endif // COUPLELIST_H
