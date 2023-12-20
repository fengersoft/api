#ifndef CSVREADER_H
#define CSVREADER_H

#include <QObject>
#include <QFile>
#include <QDebug>

#include <QTextCodec>


#include "../file/ioutils.h"
#include <QList>
#include <QApplication>


class CsvReader : public QObject
{
    Q_OBJECT
public:
    explicit CsvReader(QObject* parent = nullptr);
    ~CsvReader();
    QString fileName() const;
    void setFileName(const QString& fileName);
    void loadfromFileName(QString& fileName);
    QList<QStringList> rowDatas;
    void clearRowDatas();
    const QString& breakMark() const;
    void setBreakMark(const QString& newBreakMark);

signals:
private:
    QString m_fileName;
    QString m_breakMark;

};

#endif // CSVREADER_H
