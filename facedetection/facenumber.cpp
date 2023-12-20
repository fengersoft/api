#include "facenumber.h"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

FaceNumber::FaceNumber(QObject* parent)
    : QObject{parent}
{

}

void FaceNumber::loadFromFile(QString path)
{
    Mat mat = imread(path.toLocal8Bit().data());
    resize(mat, mat, Size(256, 256));
    int ret = getPersonNumFromMat(mat);
    m_number = ret;

}
int FaceNumber::getPersonNumFromMat(Mat& mat)
{
    int ret = 0;

    if (mat.empty())
    {

        return 0;
    }

    int* pResults = NULL;
    //pBuffer is used in the detection functions.
    //If you call functions in multiple threads, please create one buffer for each thread!
    unsigned char* pBuffer = (unsigned char*)malloc(DETECT_BUFFER_SIZE);
    if (!pBuffer)
    {

        return -1;
    }


    ///////////////////////////////////////////
    // CNN face detection
    // Best detection rate
    //////////////////////////////////////////
    //!!! The input image must be a BGR one (three-channel) instead of RGB
    //!!! DO NOT RELEASE pResults !!!
    // TickMeter cvtm;
    // cvtm.start();

    pResults = facedetect_cnn(pBuffer, (unsigned char*)(mat.ptr(0)), mat.cols, mat.rows, (int)mat.step);

    // cvtm.stop();



    for (int i = 0; i < (pResults ? *pResults : 0); i++)
    {
        short* p = ((short*)(pResults + 1)) + 142 * i;
        int confidence = p[0];


        char sScore[256];
        snprintf(sScore, 256, "%d", confidence);

        if (confidence >= 30)
        {

            ret++;

        }


    }
    free(pBuffer);




    return ret;

}

int FaceNumber::number() const
{
    return m_number;
}

void FaceNumber::setNumber(int newNumber)
{
    m_number = newNumber;
}
