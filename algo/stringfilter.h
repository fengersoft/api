#ifndef STRINGFILTER_H
#define STRINGFILTER_H

#include <QObject>

bool stringContain(QString s,QString subStr);
void stringListContain(QStringList &stl,QString subStr1,QString subStr2,QList<QStringList> &outStls);
void stringListContain(QStringList &stl,QString subStr1,QString subStr2,QString subStr3,QList<QStringList> &outStls);
void getSubStringList(QStringList &stl,QStringList &subStl,int m,int n);

#endif // STRINGFILTER_H
