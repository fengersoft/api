#ifndef IMAGECOMPAREVIEWER_H
#define IMAGECOMPAREVIEWER_H

#include <QWidget>
#include "../base/widgethelper.h"
#include "../api/draw/drawobject.h"
#include "imageobject.h"
#include "qobjectdefs.h"
#include <QWheelEvent>


namespace Ui
{
class ImageCompareViewer;
}

class ImageCompareViewer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCompareViewer(QWidget* parent = nullptr);
    ~ImageCompareViewer();
    void addFile(QString pathName);



protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::ImageCompareViewer* ui;
    WidgetHelper* m_helper;
    QList<ImageObject*> m_images;
    DrawObject* m_drawObj;
private slots:
    void onRightMenuTriggered();



};

#endif // IMAGECOMPAREVIEWER_H
