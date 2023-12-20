#ifndef DATACACHEOBJECT_H
#define DATACACHEOBJECT_H

#include <QObject>
#include <functional>
#include <QVariant>
using namespace std;
class DataCacheObject;
using UpdateDataEvent = function<void(DataCacheObject*)>;
class DataCacheObject : public QObject
{
    Q_OBJECT
public:

    explicit DataCacheObject(QObject* parent = nullptr);
    void updateData(QString key);
    static UpdateDataEvent updateDataEvent;
    const QString& key() const;
    void setKey(const QString& newKey);

    const QVariant& data() const;

    void setData(const QVariant &newData);

signals:
private:
    QString m_key;
    QVariant m_data;

};

#endif // DATACACHEOBJECT_H
