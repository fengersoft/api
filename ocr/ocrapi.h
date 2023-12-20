#ifndef OCRAPI_H
#define OCRAPI_H

#include <QObject>
#include <QWidget>

#include <QThread>
#include <QScreen>
#include <QPixmap>
#include <QApplication>
#include "../ocrlib/include/tesseract/baseapi.h"

tesseract::TessBaseAPI* getOcrTextApi();
QString getOcrText(QPixmap& pix);
QString getOcrText(QImage& img);
QString getOcrText(tesseract::TessBaseAPI* api, QPixmap& pix);
QString getOcrText(tesseract::TessBaseAPI* api, QImage& img);

#endif // OCRAPI_H
