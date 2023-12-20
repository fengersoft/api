#include "imagecorrectangle.h"

ImageCorrectAngle::ImageCorrectAngle(QObject* parent)
    : QObject{parent}
{

}

QString ImageCorrectAngle::srcPath() const
{
    return m_srcPath;
}

void ImageCorrectAngle::setSrcPath(const QString& newSrcPath)
{
    m_srcPath = newSrcPath;
}

QString ImageCorrectAngle::destPath() const
{
    return m_destPath;
}

void ImageCorrectAngle::setDestPath(const QString& newDestPath)
{
    m_destPath = newDestPath;
}

void ImageCorrectAngle::startCorrect()
{
    Mat src = cv::imread(m_srcPath.toLocal8Bit().data());
    Mat gray = src.clone();
    cvtColor(gray, gray, COLOR_BGR2GRAY);
    GaussianBlur(gray, gray, Size(5, 5), 0, 0);
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(gray, gray, element);
    Canny(gray, gray, 30, 120, 3);
    imshow("test", gray);


    std::vector<std::vector<Point> > contours;
    std::vector<std::vector<Point> > f_contours;
    std::vector<cv::Point> approx2;
    double max_area = -1;
    //注意第5个参数为CV_RETR_EXTERNAL，只检索外框
    findContours(gray, f_contours, RETR_EXTERNAL, CHAIN_APPROX_TC89_KCOS); //找轮廓//求出面积最大的轮廓int max_area = 0;
    int index = -1;
    for (int i = 0; i < f_contours.size(); i++)
    {
        qDebug() << f_contours[i].size();
        double tmparea = fabs(contourArea(f_contours[i]));
        if (tmparea > max_area)
        {
            index = i;
            max_area = tmparea;
        }


    }
    qDebug() << index << f_contours.size();
    contours.push_back(f_contours[index]);

    double num = 0.001;
    std::vector<Point2f> dd;
    double d = arcLength(f_contours[index], true);

    approxPolyDP(f_contours[index], dd, f_contours[index].size() / 4, true);
    qDebug() << dd.size();
    for (int i = dd.size() - 1; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            double x = sqrt((dd[i].x - dd[j].x) * (dd[i].x - dd[j].x) +
                            (dd[i].y - dd[j].y) * (dd[i].y - dd[j].y));

            qDebug() << "x" << x << i << j <<
                     dd[i].x << dd[i].y << dd[j].x << dd[j].y;
            if (x <= 20)
            {
                qDebug() << "delete" << i;

                dd.erase(dd.begin() + i);
                break;
            }
        }
    }

    for (int i = 0; i < dd.size(); i++)
    {
        circle(src, dd[i], 3, Scalar(0, 0, 255));
        qDebug() << dd[i].x << dd[i].y;
    }


//    RotatedRect rc = minAreaRect(dd);
//    Point2f pts[4];
//    rc.points(pts);
    for (int i = 0; i < (dd.size() - 1); i++)
    {
        line(src, dd[i], dd[i + 1], Scalar(0, 0, 255));

    }
    line(src, dd[dd.size() - 1], dd[0], Scalar(0, 0, 255));


    //drawContours(src, f_contours, index, Scalar(255, 0, 0));
    imshow("test2", src);
    calcDstSize(dd);
    cv::Mat quad = cv::Mat::zeros(g_dst_hight, g_dst_width, CV_8UC3);
    std::vector<cv::Point2f> quad_pts;
    quad_pts.push_back(cv::Point2f(0, 0));
    quad_pts.push_back(cv::Point2f(quad.cols, 0));
    quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));

    quad_pts.push_back(cv::Point2f(0, quad.rows));

    cv::Mat transmtx = cv::getPerspectiveTransform(dd, quad_pts);
    cv::warpPerspective(src, quad, transmtx, quad.size());
    flip(quad, quad, 1);
    rotate(quad, quad, ROTATE_90_COUNTERCLOCKWISE);
    imshow("test3", quad);


}

Point2f ImageCorrectAngle::computeIntersect(Vec4i a, Vec4i b)
{
    int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3];
    int x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];

    if (float d = ((float)(x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)))
    {
        cv::Point2f pt;
        pt.x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
        pt.y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;
        return pt;
    }
    else
        return cv::Point2f(-1, -1);

}
//最终图像的宽度
void ImageCorrectAngle::calcDstSize(const vector<cv::Point2f>& corners)
{
    int h1 = sqrt((corners[0].x - corners[3].x) * (corners[0].x - corners[3].x) + (corners[0].y - corners[3].y) * (corners[0].y - corners[3].y));
    int h2 = sqrt((corners[1].x - corners[2].x) * (corners[1].x - corners[2].x) + (corners[1].y - corners[2].y) * (corners[1].y - corners[2].y));
    g_dst_hight = MAX(h1, h2);

    int w1 = sqrt((corners[0].x - corners[1].x) * (corners[0].x - corners[1].x) + (corners[0].y - corners[1].y) * (corners[0].y - corners[1].y));
    int w2 = sqrt((corners[2].x - corners[3].x) * (corners[2].x - corners[3].x) + (corners[2].y - corners[3].y) * (corners[2].y - corners[3].y));
    g_dst_width = MAX(w1, w2);
}

