#include "imagetheme.h"
#include "opencv2/core/types.hpp"
#include "opencv2/imgproc.hpp"
#include "qalgorithms.h"
#include "qdatetime.h"
#include "qlist.h"
#include "qmap.h"
#include "qpair.h"
#include <cmath>

ImageTheme::ImageTheme(QObject* parent)
    : QObject{parent}
{
    m_colors["黑"] = 0;
    m_colors["灰"] = 0;
    m_colors["白"] = 0;
    m_colors["红"] = 0;
    m_colors["橙"] = 0;
    m_colors["黄"] = 0;
    m_colors["绿"] = 0;
    m_colors["青"] = 0;
    m_colors["蓝"] = 0;
    m_colors["紫"] = 0;
    m_colors["它"] = 0;

}

bool ImageTheme::loadFromFile(QString filePath)
{
    QMap<QString, int> colors;



    Mat mat = imread(filePath.toLocal8Bit().data());

    if (mat.empty())
    {
        return false;
    }
    qDebug() << filePath;
    int w = 256;
    double w1 = mat.cols;
    int factor = trunc(w1 / 256);
    int h = trunc(mat.rows / factor);
    qDebug() << w << h;
    resize(mat, mat, Size(w, h));
    cvtColor(mat, mat, COLOR_BGR2HSV);


    for (int j = 0; j < mat.rows; j++)
    {
        unsigned char* data = mat.ptr<unsigned char>(j);
        for (int i = 0; i < mat.cols; i++)
        {
            int h = data[i * 3];
            int s = data[i * 3 + 1];
            int v = data[i * 3 + 2];
            data[i * 3] = 0;
            data[i * 3 + 1] = 0;
            data[i * 3 + 2] = 0;
            if (((h >= 0) && (h <= 180)) && ((s >= 0) && (s <= 255)) && ((v >= 0) && (v <= 46)))
            {
                m_colors["黑"]++;
            }
            else if (((h >= 0) && (h <= 180)) && ((s >= 0) && (s <= 43)) && ((v >= 46) && (v <= 220)))
            {
                m_colors["灰"]++;
            }
            else if (((h >= 0) && (h <= 180)) && ((s >= 0) && (s <= 30)) && ((v >= 221) && (v <= 255)))
            {
                m_colors["白"]++;
            }
            else if ((((h >= 0) && (h <= 10)) || ((h >= 156) && (h <= 180))) && ((s >= 43) && (s <= 255)) && ((v >= 46) && (v <= 255)))
            {
                m_colors["红"]++;
            }
            else if (((h >= 11) && (h <= 25)) && ((s >= 43) && (s <= 255)) && ((v >= 46) && (v <= 255)))
            {
                m_colors["橙"]++;
            }
            else if (((h >= 26) && (h <= 34)) && ((s >= 43) && (s <= 255)) && ((v >= 46) && (v <= 255)))
            {
                m_colors["黄"]++;
            }
            else if (((h >= 35) && (h <= 77)) && ((s >= 43) && (s <= 255)) && ((v >= 46) && (v <= 255)))
            {
                m_colors["绿"]++;
            }
            else if (((h >= 78) && (h <= 99)) && ((s >= 43) && (s <= 255)) && ((v >= 46) && (v <= 255)))
            {
                m_colors["青"]++;
            }
            else if (((h >= 100) && (h <= 124)) && ((s >= 43) && (s <= 255)) && ((v >= 46) && (v <= 255)))
            {
                m_colors["蓝"]++;
            }
            else if (((h >= 125) && (h <= 155)) && ((s >= 43) && (s <= 255)) && ((v >= 46) && (v <= 255)))
            {
                m_colors["紫"]++;
            }
            else
            {
                m_colors["它"]++;

            }

        }
    }
    return true;


}

QString ImageTheme::themeNames(int len)
{
    QString ret;
    QList<QPair<QString, int>> values;
    QMap<QString, int>::Iterator it = m_colors.begin();
    for (; it != m_colors.end(); ++it)
    {
        QPair<QString, int> p(it.key(), it.value());
        values << p;
    }
    qSort(values.begin(), values.end(), [](QPair<QString, int> p1, QPair<QString, int> p2)
    {
        return p1.second > p2.second;
    });

    for (int i = 0; i < values.count(); i++)
    {
        ret += values.at(i).first;
    }

    return ret.left(len);

}
