#ifndef FILEHISTORYITEM_H
#define FILEHISTORYITEM_H

#include <QObject>
#include <QFile>
#include <QDateTime>

class FileHistoryItem : public QObject
{
    Q_OBJECT
public:
    explicit FileHistoryItem(QObject* parent = nullptr);
    void addData(QString pathName);
    void addData(QByteArray data);
    QDateTime changeTime() const;
    void setChangeTime(const QDateTime& newChangeTime);
    void saveData(QString pathName);


    QString md5() const;
    void setMd5(const QString& newMd5);

    QString remark() const;
    void setRemark(const QString &newRemark);

private:
    QByteArray m_data;
    QDateTime m_changeTime;
    QString m_md5;
    QString m_remark;


signals:

};

#endif // FILEHISTORYITEM_H
