#include "fnsalt.h"



QString getSalt(int n)
{
    QString s;
    for(int i=0;i<n;i++)
    {
        int m=QRandomGenerator::global()->bounded(0,36);
        s=s+saltValue[m];
    }

    return s;

}
