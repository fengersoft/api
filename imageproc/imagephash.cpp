#include "imagephash.h"
#include "opencv2/core.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "qglobal.h"

ImagePHash::ImagePHash(QObject* parent)
    : QObject{parent}
{

}

void ImagePHash::loadFromFile(QString path)
{
    Mat src = imread(path.toLocal8Bit().data());
    cvtColor(src, src, COLOR_BGR2GRAY);
    resize(src, src, Size(32, 32));

    src.convertTo(src, CV_32F);
    Mat srcDCT;
    dct(src, srcDCT);
    srcDCT = abs(srcDCT);
    double sum = 0;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            sum += srcDCT.at<float>(i, j);

    double average = sum / 64;
    Mat phashcode = Mat::zeros(Size(8, 8), CV_8U);
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            phashcode.at<char>(i, j) = srcDCT.at<float>(i, j) > average ? 1 : 0;

    Mat hash = phashcode.reshape(0, 1).clone();
    QString ret;
    uchar* datas = hash.ptr<uchar> (0);
    for (int i = 0; i < 64; i++)
    {
        ret += QString("%1").arg(datas[i]);
    }
    m_hashValue = ret;


}

const QString& ImagePHash::hashValue() const
{
    return m_hashValue;
}

void ImagePHash::setHashValue(const QString& newHashValue)
{
    m_hashValue = newHashValue;
}

int hamingDist(QString& s1, QString& s2)
{
    int distValue = 0;

    for (int i = 0; i < 64; i++)
    {

        if (s1[i] != s2[i])
        {
            distValue++;
        }

        QString m1 = s1.mid(i + 1);
        QString m2 = s2.mid(i + 1);
        if (m1 == m2)
        {
            break;
        }

    }
    return distValue;

}
