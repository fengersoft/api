#include "picktablelineprocoperator.h"

PickTableLineProcOperator::PickTableLineProcOperator(QObject* parent)
    : AbstractImageProcOperator{parent}
{
    m_name = "取表格线";

}

void PickTableLineProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    dest = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    Mat gray, adt, hor, ver, mask;
    cvtColor(dest, gray, COLOR_RGB2GRAY);
    adaptiveThreshold(gray, adt, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 3, 3);
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(adt, adt, element);
    erode(adt, adt, element);


    Mat horElement = getStructuringElement(MORPH_RECT, Size(adt.cols / 20, 1));
    dilate(adt, hor, horElement);
    erode(adt, hor, horElement);

    Mat verElement = getStructuringElement(MORPH_RECT, Size(1, adt.rows / 20));
    dilate(adt, ver, verElement);
    erode(adt, ver, verElement);

    bitwise_or(hor, ver, mask);

    dest = dest.clone();
    for (int j = 0; j < mask.rows; j++)
    {
        uchar* maskData = mask.ptr<uchar>(j);
        uchar* destData = dest.ptr<uchar>(j);
        for (int i = 0; i < mask.cols; i++)
        {
            if (maskData[i] != 255)
            {
                destData[i * 3] = 255;
                destData[i * 3 + 1] = 255;
                destData[i * 3 + 2] = 255;
            }
        }
    }







}
