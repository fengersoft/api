#include "imagethumbnailcreator.h"
#include "qapplication.h"
#include "qfileinfo.h"
#include "qnamespace.h"
#include "qpixmap.h"
#include <cwchar>

ImageThumbnailCreator::ImageThumbnailCreator(QObject* parent)
    : QObject{parent}
{
    m_thumbnailFolder = QApplication::applicationDirPath() + "/thumbnail";

}

const QString& ImageThumbnailCreator::thumbnailFolder() const
{
    return m_thumbnailFolder;
}

void ImageThumbnailCreator::setThumbnailFolder(const QString& newThumbnailFolder)
{
    m_thumbnailFolder = newThumbnailFolder;
}

const QString& ImageThumbnailCreator::sourceFolder() const
{
    return m_sourceFolder;
}

void ImageThumbnailCreator::setSourceFolder(const QString& newSourceFolder)
{
    m_sourceFolder = newSourceFolder;
}

void ImageThumbnailCreator::createThumbnailImages(QString sourceFolder)
{
    m_sourceFolder = sourceFolder;
    FileSeacher* searcher = new FileSeacher(this);
    connect(searcher, &FileSeacher::findFileInfo, this, [this](QString rootPath, QFileInfo & fileInfo)
    {
        if (fileInfo.isDir())
        {
            return;
        }
        if (!((fileInfo.suffix().toLower() != "jpg") || (fileInfo.suffix().toLower() != "jpeg")))
        {
            return;
        }
        QString uuid = filePathUuid(fileInfo);
        QString thumbPath = m_thumbnailFolder + "/" + uuid + "." + fileInfo.suffix();
        if (!QFile::exists(thumbPath))
        {
            QPixmap pix(fileInfo.absoluteFilePath());
            pix = pix.scaledToWidth(640, Qt::SmoothTransformation);
            pix.save(thumbPath, fileInfo.suffix().toLocal8Bit().data());

        }
        qDebug() << fileInfo.absoluteFilePath();
    });
    searcher->startSearch(m_sourceFolder);

    delete searcher;

}

QString thumbnailFilePath(QString path, QString thumbnailFolder)
{
    QFileInfo info(path);
    QString thumbnailFilePath = thumbnailFolder + "/" + filePathUuid(path) + "." + info.suffix();
    if (QFile::exists(thumbnailFilePath))
    {
        return thumbnailFilePath;
    }
    else
    {
        return path;
    }


}

QString thumbnailFilePath(QString path)
{
    return thumbnailFilePath(path, QApplication::applicationDirPath() + "/thumbnail");

}
