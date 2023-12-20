#ifndef COUPLE_H
#define COUPLE_H

#include <QObject>
#include <QString>
template<typename T>
class Couple
{
public:
    Couple(T t1, T t2)
    {
        m_t1 = t1;
        m_t2 = t2;
    }
    inline T other(T t, bool* b = nullptr)
    {
        if (b != nullptr)
        {
            *b = true;
        }

        if (m_t1 == t)
        {
            return m_t2;
        }
        else if (m_t2 == t)
        {
            return m_t1;
        }



        if (b != nullptr)
        {
            *b = false;
        }
        return t;
    }
private:
    T m_t1;
    T m_t2;

};

#endif // COUPLE_H
