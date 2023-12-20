#ifndef IMAGEFORMATCONVERTER_H
#define IMAGEFORMATCONVERTER_H

#include <QObject>
#include <QSet>
#include <QFileInfo>
#include <QDebug>
#include "../file/fileseacher.h"
#include <QImageReader>
#include <QImageWriter>

class ImageFormatConverter : public QObject
{
    Q_OBJECT
public:
    explicit ImageFormatConverter(QObject* parent = nullptr);

    const QSet<QString>& srcFormats() const;
    void setSrcFormats(const QSet<QString>& newSrcFormats);



    const QStringList& srcFiles() const;
    void setSrcFiles(const QStringList& newSrcFiles);

    const QString& destFolder() const;
    void setDestFolder(const QString& newDestFolder);
    void startConvert();

    const QString& destFormat() const;
    void setDestFormat(const QString& newDestFormat);
    void loadSrcFilesFromFolder(QString folder);

signals:
private:
    QSet<QString> m_srcFormats;
    QString m_destFormat;
    QStringList m_srcFiles;
    QString m_destFolder;

};

#endif // IMAGEFORMATCONVERTER_H
