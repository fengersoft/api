#ifndef FNLIST_H
#define FNLIST_H

#include <QObject>
#include <functional>
#include <QList>

namespace Fn {



template<typename T>
inline T findOne(QList<T> &list,T defaultValue,std::function<bool(T)> func)
{
    for(int i=0;i<list.count();i++)
    {
        T t=list.at(i);
        if (func(t))
        {
            return t;
        }

    }
    return defaultValue;
}
template<typename T>
inline QList<T> findAll(QList<T> &list,std::function<bool(T)> func)
{
    QList<T> retList;
    for(int i=0;i<list.count();i++)
    {
        T t=list.at(i);
        if (func(t))
        {
            retList<<t;
        }

    }
    return retList;
}
template<typename T>
inline QList<T> notMatch(QList<T> &list,std::function<bool(T)> func)
{
    QList<T> retList;
    for(int i=0;i<list.count();i++)
    {
        T t=list.at(i);
        if (func(t)==false)
        {
            retList<<t;
        }

    }
    return retList;
}

template<typename T>
inline QList<T> &forEach(QList<T> &list,std::function<void(T)> func)
{
    for(int i=0;i<list.count();i++)
    {
        T t=list.at(i);
        func(t);

    }
    return list;

}

///移除
template<typename T>
inline QList<T> &remove(QList<T> &list,std::function<bool(T)> func)
{
    for(int i=list.count()-1;i>=0;i--)
    {
        T t=list.at(i);
        bool f=func(t);
        if (f)
        {
            list.removeAt(i);
            delete t;
        }

    }
    return list;

}

///合并
template<typename T>
inline QList<T> merge(QList<T> list1,QList<T> list2)
{
    QList<T> list;
    for(int i=0;i<list1.count();i++)
    {
        list<<list1.at(i);
    }
    for(int i=0;i<list2.count();i++)
    {
        list<<list2.at(i);
    }

    return list;
}


///求和
template<typename T,typename N>
inline N sum(QList<T> &list,std::function<N(T)> func)
{
    N n=0;
    for(int i=0;i<list.count();i++)
    {
        T t=list.at(i);
        n+=func(t);

    }
    return n;
}


}

#endif // FNLIST_H
