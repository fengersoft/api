#include "fnstorage.h"

FnStorage::FnStorage(QObject* parent)
    : QObject{parent}
{

}

void FnStorage::setItem(QString key, QString value)
{
    m_stringMap[key] = value;

}

void FnStorage::setItem(QString key, int value)
{
    m_intMap[key] = value;

}

void FnStorage::setItem(QString key, QJsonObject value)
{
    m_jsonObjectMap[key] = value;

}

void FnStorage::setItem(QString key, QDate value)
{
    m_dateMap[key] = value;

}

void FnStorage::save(QString fileName)
{
    QJsonObject jobj;

    saveItemsData<QString>(jobj, "stringMap", m_stringMap);
    saveItemsData<int>(jobj, "intMap", m_intMap);
    saveItemsData<QJsonObject>(jobj, "jsonObjectMap", m_jsonObjectMap);






    QJsonDocument jdoc;
    jdoc.setObject(jobj);
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.write(jdoc.toJson());
    file.close();


}
template<>
QString FnStorage::item(QString key)
{
    return m_stringMap[key];
}

template<>
int FnStorage::item(QString key)
{
    return m_intMap[key];
}
template<>
QJsonObject FnStorage::item(QString key)
{
    return m_jsonObjectMap[key];
}
template<>
QDate FnStorage::item(QString key)
{
    return m_dateMap[key];
}





