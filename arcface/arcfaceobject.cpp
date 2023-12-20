#include "arcfaceobject.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

ArcFaceObject::ArcFaceObject(QObject* parent)
    : QObject{parent}
{
    m_appKey = "DUuMMi2jVamzMCwgHHYNYq3skvitbpTD9uQkwSvJyV4t";
    m_sdkKey = "Conx3qH4BqnkSyvXqzAD8JqeUSU2tLCX5npcYLcWhaoZ";


}

void ArcFaceObject::loadFromFile(QString path)
{

    ASF_ActiveFileInfo activeFileInfo = { };
    MRESULT res = ASFGetActiveFileInfo(&activeFileInfo);
    if (res != MOK)
    {

        // qDebug() << "ASFGetActiveFileInfo fail:" << res;
    }
    else
    {

    }

    const ASF_VERSION version = ASFGetVersion();

    m_versionInfo = QString("%1 %2 %3").arg(version.Version).arg(version.BuildDate).arg(version.CopyRight);


    //激活接口,首次激活需联网
    res = ASFOnlineActivation(m_appKey.toStdString().data(), m_sdkKey.toStdString().data());
    if (MOK != res && MERR_ASF_ALREADY_ACTIVATED != res)
        qDebug() << "ASFActivation fail:" << res;
    else
        qDebug() << "ASFActivation success:" << res;

    //初始化接口
    MHandle handle = NULL;
    MInt32 mask = ASF_FACE_DETECT | ASF_FACE3DANGLE | ASF_FACERECOGNITION;
    res = ASFInitEngine(ASF_DETECT_MODE_IMAGE, ASF_OP_ALL_OUT, 2, 2, mask, &handle);
//    if (res != MOK)
//        qDebug() << "ASFInitEngine fail:" << res;
//    else
//        qDebug() << "ASFInitEngine sucess:" << res;

    // 人脸检测
    Mat images[12];
    Mat srcImg = imread(path.toLocal8Bit().data());
    images[0] = srcImg.clone();
    images[1] = srcImg(Rect(0, 0, srcImg.cols, srcImg.rows / 2)).clone();
    images[2] = srcImg(Rect(0, srcImg.rows / 2, srcImg.cols, srcImg.rows / 2)).clone();
    images[3] = srcImg(Rect(0, 0, srcImg.cols / 2, srcImg.rows)).clone();
    images[4] = srcImg(Rect(srcImg.cols / 2, 0, srcImg.cols / 2, srcImg.rows)).clone();

    images[5] = srcImg(Rect(0, 0, srcImg.cols / 3, srcImg.rows)).clone();

    images[6] = srcImg(Rect(srcImg.cols / 3, 0, srcImg.cols / 3, srcImg.rows)).clone();
    images[7] = srcImg(Rect(2 * srcImg.cols / 3, 0, srcImg.cols / 3, srcImg.rows)).clone();



    images[8] = srcImg(Rect(0, 0, srcImg.cols / 2, srcImg.rows / 2)).clone();
    images[9] = srcImg(Rect(srcImg.cols / 2, 0, srcImg.cols / 2, srcImg.rows / 2)).clone();
    images[10] = srcImg(Rect(0, srcImg.rows / 2, srcImg.cols / 2, srcImg.rows / 2)).clone();
    images[11] = srcImg(Rect(srcImg.cols / 2, srcImg.rows / 2, srcImg.cols / 2, srcImg.rows / 2)).clone();
    for (int i = 0; i < 12; i++)
    {
        Mat img = images[i];
        if (!img.empty())
        {

            resize(img, img, Size(1000, 1000));

            int w = img.cols - img.cols % 4;
            img = img(Rect(0, 0, w, img.rows));

            ASF_MultiFaceInfo detectedFaces1 = { 0 };



            ASVLOFFSCREEN offscreen1 = { 0 };
            offscreen1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
            offscreen1.i32Width = img.cols;
            offscreen1.i32Height = img.rows;
            offscreen1.pi32Pitch[0] = img.step;
            offscreen1.ppu8Plane[0] = (MUInt8*)img.data;

            res = ASFDetectFacesEx(handle, &offscreen1, &detectedFaces1);

            if (MOK == res && detectedFaces1.faceNum > 0)
            {
                qDebug() << "ASFDetectFaces  success:" << res << i;
                m_hasFace = true;
                break;
            }
            else
            {
                // qDebug() << "ASFDetectFaces  fail:" << res << i;
                m_hasFace = false;

            }





        }

    }




    //反初始化
    res = ASFUninitEngine(handle);
//    if (res != MOK)
//        qDebug() << "ALUninitEngine fail:" << res;
//    else
//        qDebug() << "ALUninitEngine sucess:" << res;


}

const QString& ArcFaceObject::appKey() const
{
    return m_appKey;
}

void ArcFaceObject::setAppKey(const QString& newAppKey)
{
    m_appKey = newAppKey;
}

const QString& ArcFaceObject::sdkKey() const
{
    return m_sdkKey;
}

void ArcFaceObject::setSdkKey(const QString& newSdkKey)
{
    m_sdkKey = newSdkKey;
}

bool ArcFaceObject::hasFace() const
{
    return m_hasFace;
}

void ArcFaceObject::setHasFace(bool newHasFace)
{
    m_hasFace = newHasFace;
}

const QString& ArcFaceObject::versionInfo() const
{
    return m_versionInfo;
}

void ArcFaceObject::setVersionInfo(const QString& newVersionInfo)
{
    m_versionInfo = newVersionInfo;
}

bool hasFaceInImage(QString path)
{
    ArcFaceObject* face = new ArcFaceObject();
    face->loadFromFile(path);
    bool ret = face->hasFace();
    delete face;
    return ret;

}
