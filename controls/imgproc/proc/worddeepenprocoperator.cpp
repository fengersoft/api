#include "worddeepenprocoperator.h"

WordDeepenProcOperator::WordDeepenProcOperator(QObject* parent) : AbstractImageProcOperator(parent)
{
    m_name = "字迹加深";

}

void WordDeepenProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{

    qDebug() << "字迹加深";
    for (int j = 0; j < src.rows; j++)
    {
        uchar* data = src.ptr<uchar>(j);
        for (int i = 0; i < src.cols; i++)
        {
            int r = data[i * 3];
            int g = data[i * 3 + 1];
            int b = data[i * 3 + 2];

            if ((r <= 128) && (g <= 128) && (b <= 128))
            {
                qDebug() << r << g << b;
                getDeepenColor(r, g, b);
                data[i * 3] = r;
                data[i * 3 + 1] = g;
                data[i * 3 + 2] = b;
            }
        }

    }
    dest = src.clone();

}

void WordDeepenProcOperator::getDeepenColor(int& r, int& g, int& b)
{

    r = trunc(r * 0.9);
    b =  trunc(b * 0.9);
    g = trunc(g * 0.9);

}
