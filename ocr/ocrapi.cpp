#include "ocrapi.h"





QString getOcrText(QPixmap& pix)
{
    QImage img = pix.toImage();
    return getOcrText(img);
}

QString getOcrText(tesseract::TessBaseAPI* api, QPixmap& pix)
{


    api->Clear();
    QImage img = pix.toImage();

    uchar* data = img.bits();

    api->SetImage(data, img.width(), img.height(), 3, img.bytesPerLine());
    api->SetSourceResolution(96);
    std::string str;
    char* s = api->GetUTF8Text();
    str = s;
    //
    delete [] s;


    QString ret = QString::fromStdString(str);
    // qDebug() << QString::fromStdString(str);
    return ret;
}

QString getOcrText(QImage& img)
{
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    api->Init(nullptr, "chi_sim");
    api->Clear();

    uchar* data = img.bits();

    api->SetImage(data, img.width(), img.height(), 3, img.bytesPerLine());
    api->SetSourceResolution(96);
    std::string str;
    char* s = api->GetUTF8Text();
    str = s;
    //
    delete [] s;


    QString ret = QString::fromStdString(str);
    // qDebug() << QString::fromStdString(str);
    delete api;
    return ret;

}

tesseract::TessBaseAPI *getOcrTextApi()
{
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    api->Init(nullptr, "chi_sim");
    return api;

}

QString getOcrText(tesseract::TessBaseAPI *api, QImage &img)
{

    api->Clear();

    uchar* data = img.bits();

    api->SetImage(data, img.width(), img.height(), 3, img.bytesPerLine());
    api->SetSourceResolution(96);
    std::string str;
    char* s = api->GetUTF8Text();
    str = s;
    //
    delete [] s;


    QString ret = QString::fromStdString(str);

    return ret;

}
