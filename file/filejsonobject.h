#ifndef FILEJSONOBJECT_H
#define FILEJSONOBJECT_H

#include "qjsonobject.h"
#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

class FileJsonObject : public QObject
{
    Q_OBJECT
public:
    explicit FileJsonObject(QObject* parent = nullptr);

    const QString& root() const;
    void setRoot(const QString& newRoot);
    void addChildNode(QJsonObject& parentNode, QString parentPath);
    void saveToFile(QString path);

signals:
private:
    QString m_root;
    QJsonObject m_rootObject;

};

#endif // FILEJSONOBJECT_H
