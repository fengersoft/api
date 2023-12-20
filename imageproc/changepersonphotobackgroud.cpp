#include "changepersonphotobackgroud.h"

ChangePersonPhotoBackgroud::ChangePersonPhotoBackgroud(QObject *parent)
    : QObject{parent}
{

}

const QString &ChangePersonPhotoBackgroud::srcPath() const
{
    return m_srcPath;
}

void ChangePersonPhotoBackgroud::setSrcPath(const QString &newSrcPath)
{
    m_srcPath = newSrcPath;
}

const QString &ChangePersonPhotoBackgroud::destPath() const
{
    return m_destPath;
}

void ChangePersonPhotoBackgroud::setDestPath(const QString &newDestPath)
{
    m_destPath = newDestPath;
}

void ChangePersonPhotoBackgroud::convert()
{

    Mat src = imread(QString("e:\\重要截图\\mmexport1632227205537.jpg").toLocal8Bit().data());
        imshow("src", src);
        Rect ccomp;
        floodFill(src, Point(0, 0), Scalar(255, 0, 0), &ccomp, Scalar(20, 20, 20),
         Scalar(20, 20, 20));
        imshow("【效果图】", src);



}
