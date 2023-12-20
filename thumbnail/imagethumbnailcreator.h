#ifndef IMAGETHUMBNAILCREATOR_H
#define IMAGETHUMBNAILCREATOR_H

#include <QObject>
#include "../api/file/fileseacher.h"
#include "../api/global/globaldata.h"

class ImageThumbnailCreator : public QObject
{
    Q_OBJECT
public:
    explicit ImageThumbnailCreator(QObject* parent = nullptr);

    const QString& thumbnailFolder() const;
    void setThumbnailFolder(const QString& newThumbnailFolder);

    const QString& sourceFolder() const;
    void setSourceFolder(const QString& newSourceFolder);
    void createThumbnailImages(QString sourceFolder);

signals:
private:
    QString m_thumbnailFolder;
    QString m_sourceFolder;

};
QString thumbnailFilePath(QString path, QString thumbnailFolder);
QString thumbnailFilePath(QString path);
#endif // IMAGETHUMBNAILCREATOR_H
