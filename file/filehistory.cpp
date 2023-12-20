#include "filehistory.h"

FileHistory::FileHistory(QObject* parent)
    : QObject{parent}
{

}

QString FileHistory::pathName() const
{
    return m_pathName;
}

void FileHistory::setPathName(const QString& newPathName)
{
    m_pathName = newPathName;
    QFileInfo info(m_pathName);
    m_ext = info.suffix();
    addHistory();
}

void FileHistory::addHistory()
{
    QByteArray data = getData();
    QString md5 = getMd5(data);
    if (m_md5 == md5)
    {
        return;
    }
    m_md5 = md5;
    FileHistoryItem* item = new FileHistoryItem(this);
    item->setMd5(m_md5);
    qDebug() << md5;
    item->addData(data);
    m_items << item;

}

void FileHistory::saveAllHistory(QString path, QString prefix)
{
    for (int i = 0; i < m_items.count(); i++)
    {
        FileHistoryItem* item = m_items.at(i);
        item->saveData(path + prefix + QString("%1").arg(i + 1) + "." +
                       m_ext);
    }

}

QString FileHistory::ext() const
{
    return m_ext;
}

void FileHistory::setExt(const QString& newExt)
{
    m_ext = newExt;
}

QByteArray FileHistory::getData()
{
    QByteArray data;
    QFile file(m_pathName);
    file.open(QFile::ReadOnly);
    data = file.readAll();
    file.close();
    return data;
}

QString FileHistory::getMd5(QByteArray& data)
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(data);
    return hash.result().toHex();
}
