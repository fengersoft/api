#ifndef FACENUMBER_H
#define FACENUMBER_H

#include <QObject>
#include "facedetection/facedetectcnn.h"
#include "facedetection/facedetection_export.h"
#include "opencv2/opencv.hpp"
#include <QDebug>
using namespace cv;
#define DETECT_BUFFER_SIZE  0x20000
class FaceNumber : public QObject
{
    Q_OBJECT
public:
    explicit FaceNumber(QObject* parent = nullptr);
    void loadFromFile(QString path);
    int getPersonNumFromMat(Mat& mat);
    int number() const;
    void setNumber(int newNumber);

signals:
private:
    int m_number;

};

#endif // FACENUMBER_H
