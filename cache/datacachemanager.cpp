#include "datacachemanager.h"

DataCacheManager::DataCacheManager(QObject* parent)
    : QObject{parent}
{


}

DataCacheObject* DataCacheManager::get(QString key)
{
    DataCacheObject* obj = m_objects.value(key, nullptr);
    if (obj == nullptr)
    {
        obj = new DataCacheObject(this);
        obj->updateData(key);
        m_objects[key] = obj;

    }
    return obj;

}

DataCacheObject* DataCacheManager::getNew(QString key)
{
    DataCacheObject* obj = m_objects.value(key, nullptr);
    if (obj == nullptr)
    {
        obj = new DataCacheObject(this);


    }
    obj->updateData(key);
    m_objects[key] = obj;
    return obj;


}
