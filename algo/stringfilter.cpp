#include "stringfilter.h"



bool stringContain(QString s, QString subStr)
{
    while (subStr.indexOf("  ")>=0) {
        subStr=subStr.replace("  "," ");
    }
    subStr=subStr.trimmed();
    bool ret=true;
    QStringList stl=subStr.split(" ");
    for(int i=0;i<stl.count();i++)
    {
        if (!s.contains(stl[i],Qt::CaseInsensitive))
        {
            ret=false;
            break;
        }
    }


    return ret;
}

void stringListContain(QStringList &stl, QString subStr1, QString subStr2, QList<QStringList> &outStls)
{
    bool startTag=false;

    int startTagIndex=0;
    int endTagIndex=0;
    for (int i=0;i<stl.count();i++)
    {
        if (startTag==false)
        {
           bool b=stringContain(stl[i],subStr1);
            if (b)
           {
               startTag=true;
                startTagIndex=i;
           }
        }else
        {
           if (stringContain(stl[i],subStr1))
           {
                startTagIndex=i;
           }
           bool b=stringContain(stl[i],subStr2);
           if (b)
           {

                endTagIndex=i;
                QStringList subStl;
                getSubStringList(stl,subStl,startTagIndex,endTagIndex);
                outStls<<subStl;
                startTag=false;

           }
        }


    }

}

void getSubStringList(QStringList &stl, QStringList &subStl, int m, int n)
{
    if ((m<0) || (m>(stl.count()-1)))
    {
        return;
    }
    if ((n<0) || (n>(stl.count()-1)))
    {
        return;
    }
    for(int i=m;i<=n;i++)
    {
        subStl<<stl[i];
    }

}

void stringListContain(QStringList &stl, QString subStr1, QString subStr2, QString subStr3, QList<QStringList> &outStls)
{
    bool startTag=false;
    bool middleTag=false;

    int startTagIndex=0;
    int middleTagIndex=0;
    int endTagIndex=0;
    for (int i=0;i<stl.count();i++)
    {
        if (startTag==false)
        {
           bool b=stringContain(stl[i],subStr1);
           if (b)
           {
                startTag=true;
                startTagIndex=i;
           }
        }else
        {
           if (stringContain(stl[i],subStr1))
           {
                startTagIndex=i;
           }

           if (middleTag==false)
           {
                bool b=stringContain(stl[i],subStr2);
                if (b)
                {

                    middleTag=true;

                }
           }else
           {    bool b=stringContain(stl[i],subStr3);
                if (b==true)
                {
                    endTagIndex=i;
                    QStringList subStl;
                    getSubStringList(stl,subStl,startTagIndex,endTagIndex);
                    outStls<<subStl;
                    startTag=false;
                    middleTag=false;
                }

           }


        }


    }

}
