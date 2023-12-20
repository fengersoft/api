#include "deleteimagetask.h"

DeleteImageTask::DeleteImageTask(QObject *parent)
    : AbstractTask{parent}
{
    m_maxWidth=1080;
    m_maxHeight=1080;
    m_taskType="按图像尺寸删除";


}

const QString &DeleteImageTask::folderPath() const
{
    return m_folderPath;
}

void DeleteImageTask::setFolderPath(const QString &newFolderPath)
{
    m_folderPath = newFolderPath;
}





void DeleteImageTask::runTask()
{
    m_files.clear();
    FileSeacher *searcher=new FileSeacher(this);
    connect(searcher,&FileSeacher::findFileInfo,this,[this](QString rootPath, QFileInfo& fileInfo){
        if (fileInfo.isFile())
            {
           m_files<<fileInfo;
    }

});
    searcher->startSearch(m_folderPath);

    delete searcher;
    QSet<QString> suffixes;
    suffixes<<"png"<<"jpeg"<<"jpg"<<"bmp"<<"webp";
    emit printLog(QString("%1").arg(m_files.count()));
    QStringList fileNames;
    for(const QFileInfo &fileInfo:m_files)
    {
        QString suffix=fileInfo.suffix().toLower();

        if (!suffixes.contains(suffix))
        {
            continue;
        }
        QImageReader reader(fileInfo.absoluteFilePath());
        QSize sz=reader.size();

        if ((sz.width()>0) &&(sz.height()>0) &&(sz.width()<=m_maxWidth) && (sz.height()<=m_maxHeight))
        {
            QString path=fileInfo.absoluteFilePath();
            fileNames<<path;



        }

    }
    for(const QString &path:fileNames)
    {

        bool ret=QFile::remove(path);
        QString retInfo=ret?"成功":"失败";

        emit printLog("删除"+path+" "+retInfo);
        QApplication::processEvents();
    }


}

int DeleteImageTask::maxHeight() const
{
    return m_maxHeight;
}

void DeleteImageTask::setMaxHeight(int newMaxHeight)
{
    m_maxHeight = newMaxHeight;
}

int DeleteImageTask::maxWidth() const
{
    return m_maxWidth;
}

void DeleteImageTask::setMaxWidth(int newMaxWidth)
{
    m_maxWidth = newMaxWidth;
}
