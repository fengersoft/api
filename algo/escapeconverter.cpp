#include "escapeconverter.h"

EscapeConverter::EscapeConverter(QObject *parent)
    : QObject{parent}
{

}

QString EscapeConverter::decode(const QString s)
{
    QString ret=s;
    ret=ret.replace("&lt;","<");
     ret=ret.replace("&gt;",">");
     return ret;

}
