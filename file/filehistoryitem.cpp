#include "filehistoryitem.h"

FileHistoryItem::FileHistoryItem(QObject* parent)
    : QObject{parent}
{

}

void FileHistoryItem::addData(QString pathName)
{
    m_changeTime = QDateTime::currentDateTime();
    QFile file(pathName);
    file.open(QIODevice::ReadOnly);
    m_data = file.readAll();
    file.close();

}

void FileHistoryItem::addData(QByteArray data)
{
    m_changeTime = QDateTime::currentDateTime();
    m_data = data;

}

QDateTime FileHistoryItem::changeTime() const
{
    return m_changeTime;
}

void FileHistoryItem::setChangeTime(const QDateTime& newChangeTime)
{
    m_changeTime = newChangeTime;
}

void FileHistoryItem::saveData(QString pathName)
{
    QFile file(pathName);
    file.open(QFile::WriteOnly);
    file.write(m_data);
    file.close();

}

QString FileHistoryItem::md5() const
{
    return m_md5;
}

void FileHistoryItem::setMd5(const QString &newMd5)
{
    m_md5 = newMd5;
}

QString FileHistoryItem::remark() const
{
    return m_remark;
}

void FileHistoryItem::setRemark(const QString &newRemark)
{
    m_remark = newRemark;
}


