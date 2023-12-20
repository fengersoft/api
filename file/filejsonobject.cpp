#include "filejsonobject.h"
#include "qdir.h"
#include "qfileinfo.h"
#include "qjsondocument.h"
#include "qjsonvalue.h"

FileJsonObject::FileJsonObject(QObject* parent)
    : QObject{parent}
{

}

const QString& FileJsonObject::root() const
{
    return m_root;
}

void FileJsonObject::setRoot(const QString& newRoot)
{
    m_root = newRoot;

    addChildNode(m_rootObject, m_root);

}

void FileJsonObject::addChildNode(QJsonObject& parentNode, QString parentPath)
{
    QDir dir(parentPath);
    QFileInfo parentInfo(parentPath);
    parentNode["name"] = parentInfo.fileName();
    parentNode["isDir"] = parentInfo.isDir();
    parentNode["path"] = parentInfo.absoluteFilePath();
    QFileInfoList fileInfos = dir.entryInfoList();

    QJsonArray children;
    for (const QFileInfo& info : fileInfos)
    {
        if ((info.fileName() == ".") || (info.fileName() == ".."))
        {
            continue;
        }
        QJsonObject childNode;
        childNode["name"] = info.fileName();
        childNode["isDir"] = info.isDir();
        childNode["path"] = info.absoluteFilePath();


        if (info.isDir())
        {

            addChildNode(childNode, info.absoluteFilePath());
        }
        children.append(childNode);


    }
    parentNode["children"] = children;
}

void FileJsonObject::saveToFile(QString path)
{
    QJsonDocument jdoc;
    jdoc.setObject(m_rootObject);
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(jdoc.toJson());
    file.close();

}
