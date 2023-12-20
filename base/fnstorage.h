#ifndef FNSTORAGE_H
#define FNSTORAGE_H

#include <QObject>
#include <QMap>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

class FnStorage : public QObject
{
    Q_OBJECT
public:
    explicit FnStorage(QObject* parent = nullptr);
    void setItem(QString key, QString value);
    void setItem(QString key, int value);
    void setItem(QString key, QJsonObject value);
    void setItem(QString key, QDate value);

    template<typename T>
    T item(QString key);

    void save(QString fileName);

    template<typename T>
    inline void saveItemsData(QJsonObject& jobj, QString key, QMap<QString, T>& mapData)
    {
        QJsonObject jdata;
        auto it = mapData.begin();
        for (; it != mapData.end(); it++)
        {
            jdata[it.key()] = it.value();

        }
        jobj[key] = jdata;
    }












signals:
private:
    QMap<QString, QString> m_stringMap;
    QMap<QString, int> m_intMap;
    QMap<QString, QJsonObject> m_jsonObjectMap;
    QMap<QString, QDate> m_dateMap;


};

#endif // FNSTORAGE_H
