#ifndef FILEHISTORY_H
#define FILEHISTORY_H

#include <QObject>
#include <QList>
#include <QFileInfo>
#include "filehistoryitem.h"
#include <QCryptographicHash>

class FileHistory : public QObject
{
    Q_OBJECT
public:
    explicit FileHistory(QObject* parent = nullptr);
    QString pathName() const;
    void setPathName(const QString& newPathName);
    void addHistory();
    void saveAllHistory(QString path, QString prefix = "");

    QString ext() const;
    void setExt(const QString& newExt);
    QByteArray getData();
    QString getMd5(QByteArray& data);

private:
    QString m_pathName;
    QList<FileHistoryItem*> m_items;
    QString m_ext;
    QString m_md5;

signals:

};

#endif // FILEHISTORY_H
