
#include "urlparse.h"



QString getDomainNameFromUrl(QString url)
{
    QString ret = "";
    int n = url.indexOf("//");
    QString s = url.mid(n + 2);

    n = s.indexOf("/");
    s = s.left(n);
    QStringList stl = s.split(".");
    if (stl.count() >= 2)
    {
        int m = stl.count() - 2;
        ret = stl[m];
    }
    return ret;
}
