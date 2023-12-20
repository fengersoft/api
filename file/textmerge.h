#ifndef TEXTMERGE_H
#define TEXTMERGE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "ioutils.h"

class TextMerge : public QObject
{
    Q_OBJECT
public:
    explicit TextMerge(QObject* parent = nullptr);

    const QStringList& fileNames() const;
    void setFileNames(const QStringList& newFileNames);
    void merge(QString fileName);
signals:
private:
    QStringList m_fileNames;

};

#endif // TEXTMERGE_H
