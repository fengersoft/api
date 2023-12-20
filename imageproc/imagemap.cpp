#include "imagemap.h"

ImageMap::ImageMap(QObject* parent)
    : QObject{parent}
{

}

void ImageMap::addImage(QString name, QString path, QColor color)
{
    int r, g, b;
    color.getRgb(&r, &g, &b);
    QImage img(path);

    for (int j = 0; j < img.height(); j++)
    {
        uchar* data = img.scanLine(j);
        for (int i = 0; i < img.width(); i++)
        {
            if (data[i * 4 + 3] != 0)
            {
                data[i * 4] = b;
                data[i * 4 + 1] = g;
                data[i * 4 + 2] = r;
            }

        }

    }
    m_images.insert(name, QPixmap::fromImage(img));

}

QPixmap ImageMap::pixmap(QString name)
{
    return m_images.value(name);

}
