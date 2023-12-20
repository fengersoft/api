#include "imageformatconverter.h"
#include "qapplication.h"
#include "qfileinfo.h"
#include "qimagewriter.h"
#include "qpixmap.h"

ImageFormatConverter::ImageFormatConverter(QObject* parent)
    : QObject{parent}
{
    qDebug() << QImageWriter::supportedImageFormats();
    qDebug() << QImageWriter::supportedImageFormats();

}

const QSet<QString>& ImageFormatConverter::srcFormats() const
{
    return m_srcFormats;
}

void ImageFormatConverter::setSrcFormats(const QSet<QString>& newSrcFormats)
{
    m_srcFormats = newSrcFormats;
}



const QStringList& ImageFormatConverter::srcFiles() const
{
    return m_srcFiles;
}

void ImageFormatConverter::setSrcFiles(const QStringList& newSrcFiles)
{
    m_srcFiles = newSrcFiles;
}

const QString& ImageFormatConverter::destFolder() const
{
    return m_destFolder;
}

void ImageFormatConverter::setDestFolder(const QString& newDestFolder)
{
    m_destFolder = newDestFolder;
}

void ImageFormatConverter::startConvert()
{
    QFileInfo destFolder(m_destFolder);
    QString destFolderPath = destFolder.absoluteFilePath();
    for (int i = 0; i < m_srcFiles.count(); i++)
    {
        QPixmap pix(m_srcFiles[i]);

        QFileInfo info(m_srcFiles[i]);
        int n = info.fileName().lastIndexOf(".");
        QString destPath = destFolderPath + "/" + info.fileName().left(n + 1) + m_destFormat;
        if (m_destFormat == "jpg")
        {
            pix.save(destPath, "jpg", 100);
        }
        else
        {
            pix.save(destPath, QString(m_destFormat).toStdString().data());
        }
        QApplication::processEvents();



    }

}

const QString& ImageFormatConverter::destFormat() const
{
    return m_destFormat;
}

void ImageFormatConverter::setDestFormat(const QString& newDestFormat)
{
    m_destFormat = newDestFormat;
}

void ImageFormatConverter::loadSrcFilesFromFolder(QString folder)
{
    FileSeacher* searcher = new FileSeacher(this);
    connect(searcher, &FileSeacher::findFileInfo, this, [this](QString rootPath, QFileInfo & fileInfo)
    {
        m_srcFiles << fileInfo.absoluteFilePath();
    });
    searcher->startSearch(folder);

    delete searcher;

}
