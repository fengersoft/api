#include "mustacheobject.h"

MustAcheObject::MustAcheObject(QObject* parent)
    : QObject{parent}
{

}

QString MustAcheObject::value(QString src, QMap<QString, QString> params)
{
    QString ret = src;
    QStringList keys;
    int n;
    int s = 0;
    while ((n = ret.indexOf("}}", s)) >= 0)
    {

        int m = src.lastIndexOf("{{", n);
        if ((m >= 0) && (n >> 0))
        {
            QString key = ret.mid(m, n - m + 2);

            s = n + 2;
            keys << key;


        }
        else
        {
            break;
        }

    }
    for (const QString& key : keys)
    {

        QString sKey = key.mid(2, key.length() - 4).trimmed();
        if (params.contains(sKey))
        {
            ret = ret.replace(key, params[sKey]);
        }

    }


    return ret;

}

QString mustAcheString(QString src, QMap<QString, QString> params)
{
    MustAcheObject* obj = new MustAcheObject();

    QString ret = obj->value(src, params);
    delete obj;
    return ret;

}
