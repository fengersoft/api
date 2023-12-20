#include "removeselstainsprocoperator.h"
#include "abstractimageprocoperator.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/imgcodecs.hpp"

RemoveSelStainsProcOperator::RemoveSelStainsProcOperator(QObject* parent)
    : AbstractImageProcOperator{parent}
{
    m_name = "局部去污";

}
void RemoveSelStainsProcOperator::operatorImage(Mat& src, Mat& dest, ImageProcInfo& info)
{
    dest = src.clone();
    Rect roi(info.selLeft, info.selTop, info.selWidth, info.selHeight);
    Mat tmp = dest(roi);
    qDebug() << tmp.cols << tmp.rows;
    removeStains(tmp, 0, 0, tmp.cols - 1, tmp.rows - 1, info);




}
void RemoveSelStainsProcOperator::removeStains(Mat& imgData, int x, int y, int w, int h, ImageProcInfo& info)
{
    // Declares a vector of vectors for store the contours
    Mat originalimage;

    // Loads the original image
    Rect rc;
    rc.x = x;
    rc.y = y;
    rc.width = w;
    rc.height = h;
    originalimage = imgData(rc);
    Mat image = Mat(originalimage.rows, originalimage.cols, CV_8UC1);
    for (int j = 0; j < image.rows; j++)
    {
        uchar* src = originalimage.ptr<uchar>(j);
        uchar* dest = image.ptr<uchar>(j);
        for (int i = 0; i < image.cols; i++)
        {
            if (isHdBackColor(src[i * 3], src[i * 3 + 1], src[i * 3 + 2]))
                dest[i] = 255;
            else
                dest[i] = 0;
        }
    }

    // Finds contours
    vector<vector<Point>> v;
    vector<Vec4i> hierarchy;
    Rect rect;
    findContours(image, v, hierarchy, RETR_CCOMP, CHAIN_APPROX_NONE);
    for (size_t i = 0; i < hierarchy.size(); i++)
    {
        rect = boundingRect(v.at(i));

        // 画最小的圆，贴着黑色
        if ((rect.width <= info.stainWidth) && (rect.height <= info.stainWidth))
        {
            if ((rect.width > 0) && (rect.height > 0)
                && (rect.x >= 0) && (rect.y >= 0)
                && ((rect.x + rect.width) < originalimage.cols)
                && ((rect.y + rect.height) < originalimage.rows) && (rect.empty() == false))
            {
                Mat tmp = originalimage(rect);
                for (int n = 0; n < tmp.rows; n++)
                {
                    uchar* data = tmp.ptr<uchar>(n);
                    for (int m = 0; m < tmp.cols; m++)
                    {
                        data[m * 3] = 254;
                        data[m * 3 + 1] = 247;
                        data[m * 3 + 2] = 197;
                    }
                }
            }
        }
    }


}
inline bool RemoveSelStainsProcOperator::isHdBackColor(int r, int g, int b)
{
    int r0 = abs(r - 254);
    int g0 = abs(g - 247);
    int b0 = abs(b - 197);
    if ((r0 <= 10) && (g0 <= 10) && (b0 <= 10))
        return true;
    else
        return false;
}
