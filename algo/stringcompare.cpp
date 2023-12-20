#include "stringcompare.h"

StringCompare::StringCompare(QObject *parent)
    : QObject{parent}
{

}

const QString &StringCompare::value1() const
{
    return m_value1;
}

void StringCompare::setValue1(const QString &newValue1)
{
    m_value1 = newValue1;
}

const QString &StringCompare::value2() const
{
    return m_value2;
}

void StringCompare::setValue2(const QString &newValue2)
{
    m_value2 = newValue2;
}

int StringCompare::sameNumber()
{
    int n=0;
    QString s1=m_value1.length()>=m_value2.length()?m_value1:m_value2;
    QString s2=m_value1.length()<m_value2.length()?m_value1:m_value2;
    int start=0;
    int end=s2.length();
    while (start<end)
    {
        QString s=s2.mid(start,end);
        QString t=s;
        while (true)
        {
            int m=s1.indexOf(t);
            if (m>=0)
            {
                n+=t.length();
                start+=t.length();
                s1=s1.mid(m+t.length());
                break;
            }else
            {
                t=t.left(t.length()-1);
            }
            if (t=="")
            {
                start++;
                break;
            }
        }

    }
    return n;

}
