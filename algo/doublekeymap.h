#ifndef DOUBLEKEYMAP_H
#define DOUBLEKEYMAP_H
#include <QMap>
#include <QPair>
#include <tuple>
template<typename K1, typename K2, typename V>
class DoubleKeyMap
{
public:

    inline V get(K1 k1, K2 k2, V defaultValue)
    {
        if (!m_datas.contains({k1, k2}))
        {
            return defaultValue;
        }

        return m_datas[ {k1, k2}];
    }
    inline V operator[](std::tuple<K1, K2, V> s)
    {

        return get(std::get<0>(s), std::get<1>(s),
                   std::get<2>(s));
    }


    inline void put(K1 k1, K2 k2, V v)
    {

        m_datas[ {k1, k2}] = v;

    }
    inline bool exist(K1 k1, K2 k2)
    {

        return m_datas.contains({k1, k2});

    }
private:
    QMap<QPair<K1, K2>, V > m_datas;

};

#endif // DOUBLEKEYMAP_H
