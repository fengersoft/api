#ifndef IMAGEPAGEVIEWER_H
#define IMAGEPAGEVIEWER_H

#include <QWidget>
#include "parentimageviewer.h"
#include <QPainter>
#include "../api/draw/drawobject.h"

namespace Ui
{
class ImagePageViewer;
}

class ImagePageViewer : public ParentImageViewer
{
    Q_OBJECT

public:
    explicit ImagePageViewer(QWidget* parent = nullptr);
    ~ImagePageViewer();
protected:
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::ImagePageViewer* ui;
    DrawObject* m_drawObj;
};

#endif // IMAGEPAGEVIEWER_H
