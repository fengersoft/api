#include "removeimagecolor.h"

RemoveImageColor::RemoveImageColor(QObject *parent)
    : QObject{parent}
{
    m_colorOffSet=10;

}

const QString &RemoveImageColor::src() const
{
    return m_src;
}

void RemoveImageColor::setSrc(const QString &newSrc)
{
    m_src = newSrc;
}

const QString &RemoveImageColor::dest() const
{
    return m_dest;
}

void RemoveImageColor::setDest(const QString &newDest)
{
    m_dest = newDest;
}

const QString &RemoveImageColor::dataset() const
{
    return m_dataset;
}

void RemoveImageColor::setDataset(const QString &newDataset)
{
    m_dataset = newDataset;
    QFile file(m_dataset);
    file.open(QIODevice::ReadOnly);
    QByteArray ret=file.readAll();
    QString s=QString::fromLocal8Bit(ret);
    QStringList colors=s.split("\n");
    for (const QString &s:colors)
    {
        QStringList colorValues=s.split(",");
        if (colorValues.count()==3)
        {

          int r=colorValues[0].toInt();
          int g=colorValues[1].toInt();
          int b=colorValues[2].toInt();
          int c=(r<<16)+(g<<8)+b;

          m_dataColors<<c;
          m_cacheColors<<c;
          qDebug()<<c;

        }

    }
    file.close();

}

void RemoveImageColor::convert()
{


   Mat mat=cv::imread(QString("E:\\C 测试数据\\证件照\\01.webp").toLocal8Bit().data());

   for (int j=0;j<mat.rows;j++)
   {
       uchar* data=mat.ptr<uchar>(j);
       for(int i=0;i<mat.cols;i++)
       {
           int r=data[i*3+2];
           int g=data[i*3+1];
           int b=data[i*3];
           int c=(r<<16)+(g<<8)+b;
           if ((m_cacheColors.contains(c)) ||((r>=100) && ((g+b)<100)))
           {
               data[i*3]=255;
                data[i*3+1]=255;
                 data[i*3+2]=255;
           }


       }
   }

   imwrite("d:\\test.bmp",mat);
   imshow("test",mat);



}

int RemoveImageColor::colorOffSet() const
{
    return m_colorOffSet;
}

void RemoveImageColor::setColorOffSet(int newColorOffSet)
{
    m_colorOffSet = newColorOffSet;
}
