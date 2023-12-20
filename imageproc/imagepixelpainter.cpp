#include "imagepixelpainter.h"

ImagePixelPainter::ImagePixelPainter(QObject *parent)
    : QObject{parent}
{
    m_colorStep=32;

}

const QString &ImagePixelPainter::srcPath() const
{
    return m_srcPath;
}

void ImagePixelPainter::setSrcPath(const QString &newSrcPath)
{
    m_srcPath = newSrcPath;
}

const QString &ImagePixelPainter::destPath() const
{
    return m_destPath;
}

void ImagePixelPainter::setDestPath(const QString &newDestPath)
{
    m_destPath = newDestPath;
}

void ImagePixelPainter::convert()
{
    QImage img(m_srcPath);

    QImage newImg=img.copy();
    newImg=newImg.scaledToWidth(64);
    int h=newImg.height()*32;
    qDebug()<<newImg.width()<<newImg.height()<<img.width()<<img.height()<<h;
    QImage drawImg(QSize(2048,h),QImage::Format_RGB888);
    QPainter painter;
    painter.begin(&drawImg);
    QRect drawRect(0,0,2048,h);
    painter.fillRect(drawRect,QBrush(Qt::white));
    for(int j=0;j<newImg.height();j++)
    {
        for(int i=0;i<newImg.width();i++)
        {
            QRect cell(i*32,j*32,32,32);
            QColor c=newImg.pixelColor(i,j);
            int r,g,b;
            c.getRgb(&r,&g,&b);
            c=QColor((r/m_colorStep)*m_colorStep,(g/m_colorStep)*m_colorStep,(b/m_colorStep)*m_colorStep);
            painter.fillRect(cell,QBrush(QColor(c)));


        }

    }

    for(int j=0;j<newImg.height();j++)
    {
        for(int i=0;i<newImg.width();i++)
        {

            painter.drawLine(i*32,0,i*32,h);

        }
        painter.drawLine(0,j*32,2048,j*32);
    }
    painter.end();


    drawImg.save("d:\\ret3.bmp","bmp");



}

int ImagePixelPainter::colorStep() const
{
    return m_colorStep;
}

void ImagePixelPainter::setColorStep(int newColorStep)
{
    m_colorStep = newColorStep;
}
