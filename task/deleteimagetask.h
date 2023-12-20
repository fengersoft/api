#ifndef DELETEIMAGETASK_H
#define DELETEIMAGETASK_H

#include <QObject>
#include "abstracttask.h"
#include "../file/fileseacher.h"
#include  <QApplication>
#include <QFileInfo>
#include <QImageReader>
class DeleteImageTask : public AbstractTask
{
    Q_OBJECT
public:
    explicit DeleteImageTask(QObject *parent = nullptr);

    const QString &folderPath() const;
    void setFolderPath(const QString &newFolderPath);


    int maxWidth() const;
    void setMaxWidth(int newMaxWidth);

    int maxHeight() const;
    void setMaxHeight(int newMaxHeight);

protected:
    void runTask();

signals:
private:
    QString m_folderPath;
    int m_maxWidth;
    int m_maxHeight;
    QList<QFileInfo> m_files;

};

#endif // DELETEIMAGETASK_H
