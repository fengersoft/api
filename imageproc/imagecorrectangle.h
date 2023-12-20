#ifndef IMAGECORRECTANGLE_H
#define IMAGECORRECTANGLE_H

#include <QObject>
#include <QDebug>
#include "opencv2/opencv.hpp"

using namespace  cv;
using namespace std;

class ImageCorrectAngle : public QObject
{
    Q_OBJECT
public:
    explicit ImageCorrectAngle(QObject* parent = nullptr);

    QString srcPath() const;
    void setSrcPath(const QString& newSrcPath);

    QString destPath() const;
    void setDestPath(const QString& newDestPath);
    void startCorrect();
    cv::Point2f computeIntersect(cv::Vec4i a, cv::Vec4i b);
    void calcDstSize(const vector<cv::Point2f>& corners);



signals:
private:
    QString m_srcPath;
    QString m_destPath;
    int g_dst_hight;
    int g_dst_width;

};

#endif // IMAGECORRECTANGLE_H
