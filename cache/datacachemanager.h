#ifndef DATACACHEMANAGER_H
#define DATACACHEMANAGER_H

#include <QObject>
#include "datacacheobject.h"
#include <QMap>
class DataCacheManager : public QObject
{
    Q_OBJECT
public:
    explicit DataCacheManager(QObject* parent = nullptr);
    DataCacheObject* get(QString key);
    DataCacheObject* getNew(QString key);

signals:

private:
    QMap<QString, DataCacheObject*> m_objects;
};

#endif // DATACACHEMANAGER_H
