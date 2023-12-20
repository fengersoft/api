#ifndef IMAGEPROCVIEWER_H
#define IMAGEPROCVIEWER_H

#include <QWidget>
#include <QPainter>
#include "./proc/imageprocbase.h"
#include "../api/controls/base/widgethelper.h"
#include "../api/opencv/include/opencv2/opencv.hpp"
#include "./proc/abstractimageprocoperator.h"
#include "../api/draw/drawobject.h"
#include <math.h>
#include <QWheelEvent>
#include <QFileInfo>
#include <QDir>
#include "./history/imageprochistoryobject.h"
#include "./history/showimageprochistorydialog.h"
#include "qobjectdefs.h"
#include "qshortcut.h"
#include <QList>
#include <QShortcut>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QKeySequence>

using namespace cv;


namespace Ui
{
class ImageProcViewer;
}

class ImageProcViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageProcViewer(QWidget* parent = nullptr);
    ~ImageProcViewer();
    void loadFromFile(QString pathName);
    void getImageFromMat(Mat& src);
    void restoreFromMat(Mat& src);
    void pasteTo(Mat& src, int l, int t, int w, int h);
    void pasteTo(Mat& src, int l, int t, int w, int h, Scalar s);

    const QString& pathName() const;
    void setPathName(const QString& newPathName);
    int imgLeft() const;
    void setImgLeft(int newImgLeft);

    int imgTop() const;
    void setImgTop(int newImgTop);

    void setOperation(ImageProcOperation newOperation);
    void fitToWidth();
    void fitToHeight();
    void autoFit();
    void showOriginalSzie();
    QMap<QString, AbstractImageProcOperator*> imgProcs;

    template<typename T>
    inline void addImgProc()
    {
        T* t = new T();
        imgProcs[t->name()] = t;
    }
    void operatorImage(QString name, ImageProcInfo& info);
    void operatorImage(QString name, ImageProcInfo& info, Mat& dest);
    void reloadImgData();


    double factor() const;
    ///放大
    void zoomIn();
    ///缩小
    void zoomOut();
    ///清空图片
    void clear();
    void save();

    void setFactor(double newFactor);

    const QString& procName() const;
    void setProcName(const QString& newProcName);

    int selColorR() const;
    void setSelColorR(int newSelColorR);

    int selColorG() const;
    void setSelColorG(int newSelColorG);

    int selColorB() const;
    void setSelColorB(int newSelColorB);

    const QColor& backGroundColor() const;
    void setBackGroundColor(const QColor& newBackGroundColor);

    bool isAutoSaved() const;
    void setAutoSaved(bool newIsAutoSaved);

    bool hasEmit() const;
    void setHasEmit(bool newHasEmit);
    QList<ImageProcHistoryObject*> procHistoryList;

    //显示历史操作 对话框
    void showProcHistoryListDialog();
    ImageShowState showState() const;
    void setShowState(ImageShowState newShowState);

    void loadShortCutConfig(QString path);
    int stainWidth() const;
    void setStainWidth(int newStainWidth);

    int stainHeight() const;
    void setStainHeight(int newStainHeight);



    int threshold() const;
    void setThreshold(int newThreshold);

    bool autoThresholdValue() const;
    void setAutoThresholdValue(bool newAutoThresholdValue);

    int gammaValue() const;
    void setGammaValue(int newGammaValue);

public slots:
    void onShortCutActive();
signals:
    void afterOperatorImage(QString procName, Mat& src, Mat& dest, ImageProcInfo& info);
    void sendShortCut(QString caption);
protected:
    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::ImageProcViewer* ui;
    QString m_pathName;
    Mat m_imgData;
    QPixmap m_imgPix;
    QPixmap m_showPix;

    int m_imgLeft;
    int m_imgTop;
    WidgetHelper* m_helper;
    ImageProcOperation m_operation;
    double m_factor;
    DrawObject* m_drawObj;
    QString m_procName;
    int m_selColorR;
    int m_selColorG;
    int m_selColorB;
    int m_pickColorR;
    int m_pickColorG;
    int m_pickColorB;
    int m_stainWidth;
    int m_stainHeight;
    QColor m_backGroundColor;
    QRect m_showRect;
    bool m_isAutoSaved;
    bool m_hasEmit;
    int m_threshold;
    bool m_autoThresholdValue;
    int m_gammaValue;
    ImageShowState m_showState;
    QList<QShortcut*> m_shortCuts;
};

#endif // IMAGEPROCVIEWER_H
