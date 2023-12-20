#include "pickbluecolorprocoperator.h"

PickBlueColorProcOperator::PickBlueColorProcOperator(QObject* parent)
    : AbstractImageProcOperator{parent}
{
    m_name = "取蓝色";

}

void PickBlueColorProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    dest = src(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));
    Mat hsv = dest.clone();
    cvtColor(src, hsv, COLOR_RGB2HSV);


    cv::Mat mask;
    cv::inRange(hsv, cv::Scalar(100, 43, 56), cv::Scalar(124, 255, 255), mask);

    cv::Mat ret;
    src.copyTo(ret, mask);
    dest = ret(Rect(info.selLeft, info.selTop, info.selWidth, info.selHeight));

}
