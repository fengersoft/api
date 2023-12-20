#ifndef JSONMAP_H
#define JSONMAP_H

#include <QObject>
#include <QApplication>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include <QSharedPointer>
#include <functional>

class JsonMap : public QObject
{
    Q_OBJECT
public:
    explicit JsonMap(QObject *parent = nullptr);
    ~JsonMap();
    static JsonMap* createJsonMap(QString configName,QObject *parent = nullptr);
    const QString &filePath() const;
    void setFilePath(const QString &newFilePath);
    void setValue(QString key,QString value,bool saved=true);
    QString value(QString key,bool readFromFile=true);
    void readValue(QString key,std::function<void(QString,QString)> func);
    void saveData();
    void loadData();
    JsonMap *saveValue(QString key,QString value);
    void saveEnd();




signals:
private:
    QString m_filePath;
    QMap<QString,QString> m_map;



};
QSharedPointer<JsonMap> defaultJsonMap();

#endif // JSONMAP_H
