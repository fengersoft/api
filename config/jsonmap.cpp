#include "jsonmap.h"

JsonMap::JsonMap(QObject *parent)
    : QObject{parent}
{

}

JsonMap::~JsonMap()
{
    qDebug()<<"JsonMap::~JsonMap()";

}

JsonMap *JsonMap::createJsonMap(QString configName,QObject *parent)
{
    JsonMap *obj=new JsonMap(parent);
    obj->setFilePath(QApplication::applicationDirPath()+"/configs/"+configName+".json");
    obj->loadData();
    return obj;

}

const QString &JsonMap::filePath() const
{
    return m_filePath;
}

void JsonMap::setFilePath(const QString &newFilePath)
{
    m_filePath = newFilePath;
}

void JsonMap::setValue(QString key, QString value,bool saved)
{
    m_map[key]=value;
    if (saved)
    {
      saveData();
    }


}

QString JsonMap::value(QString key, bool readFromFile)
{
    if (readFromFile)
    {
        loadData();

    }
    return m_map.value(key,"");

}

void JsonMap::readValue(QString key, std::function<void (QString, QString)> func)
{
    QString value=this->value(key);
    func(key,value);

}

void JsonMap::saveData()
{
    QJsonObject jobj;
    QMapIterator<QString,QString> it(m_map);
    while (it.hasNext()) {
        it.next();
        jobj[it.key()]=it.value();

    }
    QJsonDocument jdoc;
    jdoc.setObject(jobj);
    QByteArray data=jdoc.toJson();
    QFile file(m_filePath);
    file.open(QIODevice::WriteOnly);
    file.write(data);
    file.close();

}

void JsonMap::loadData()
{
    QFile file(m_filePath);
    file.open(QIODevice::ReadOnly);
    QByteArray data=file.readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(data);
    QJsonObject jobj=jdoc.object();

    QStringList keys=jobj.keys();

    for(QString key:keys)
    {
        m_map[key]=jobj[key].toString();
    }



    file.close();
}

JsonMap *JsonMap::saveValue(QString key, QString value)
{
    setValue(key,value);
    return this;

}

void JsonMap::saveEnd()
{
    saveData();

}

QSharedPointer<JsonMap> defaultJsonMap()
{

    QSharedPointer<JsonMap> obj=QSharedPointer<JsonMap>(new JsonMap);
    obj->setFilePath(QApplication::applicationDirPath()+"/configs/config.json");
    obj->loadData();
    return obj;
}
