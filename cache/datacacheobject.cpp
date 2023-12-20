#include "datacacheobject.h"

UpdateDataEvent DataCacheObject::updateDataEvent = nullptr;
DataCacheObject::DataCacheObject(QObject* parent)
    : QObject{parent}
{


}

void DataCacheObject::updateData(QString key)
{
    this->setKey(key);
    if (updateDataEvent != nullptr)
    {
        updateDataEvent(this);
    }


}

const QString& DataCacheObject::key() const
{
    return m_key;
}

void DataCacheObject::setKey(const QString& newKey)
{
    m_key = newKey;
}

const QVariant& DataCacheObject::data() const
{
    return m_data;
}

void DataCacheObject::setData(const QVariant &newData)
{
    m_data = newData;
}
