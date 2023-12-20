#include "numberformatter.h"

NumberFormatter::NumberFormatter(QObject *parent)
    : QObject{parent}
{

}

QString NumberFormatter::numberToChinese(int n)
{
    QStringList nums;
    nums<<"零";
    nums<<"一";
    nums<<"二";
    nums<<"三";
    nums<<"四";
    nums<<"五";
    nums<<"六";
    nums<<"七";
    nums<<"八";
    nums<<"九";

    QStringList units;
    units<<"";
    units<<"十";
    units<<"百";
    units<<"千";
    units<<"万";
    QString s=QString("%1").arg(n);

    QString ret;
    int m=s.length()-1;
    for(int i=0;i<s.length();i++)
    {
        int v=QString(s.at(i)).toInt();
        if (v!=0)
        {
            ret+=nums[v];
            ret+=units[m];
        }else
        {
            ret+=nums[v];
        }

        m--;
    }
    if (ret.endsWith("零零"))
    {
        ret=ret.replace("零零","");
    }
    if (ret.endsWith("十零"))
    {
        ret=ret.replace("十零","十");
    }
    if (ret.endsWith("千零"))
    {
        ret=ret.replace("千零","千");
    }
    if (ret.startsWith("一十"))
    {
        ret=ret.replace("一十","十");
    }
    if (ret.startsWith("二千"))
    {
        ret=ret.replace("二千","两千");
    }
    return ret;





}
