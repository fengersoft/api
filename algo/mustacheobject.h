#ifndef MUSTACHEOBJECT_H
#define MUSTACHEOBJECT_H

#include "qmap.h"
#include <QObject>
#include <QDebug>

class MustAcheObject : public QObject
{
    Q_OBJECT
public:
    explicit MustAcheObject(QObject* parent = nullptr);
    QString value(QString src, QMap<QString, QString> params);

signals:


};
QString mustAcheString(QString src, QMap<QString, QString> params);
#endif // MUSTACHEOBJECT_H
