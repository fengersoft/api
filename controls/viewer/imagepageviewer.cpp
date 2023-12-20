#include "imagepageviewer.h"
#include "imageobject.h"
#include "parentimageviewer.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "ui_imagepageviewer.h"

ImagePageViewer::ImagePageViewer(QWidget* parent) :
    ParentImageViewer(parent),
    ui(new Ui::ImagePageViewer)
{
    ui->setupUi(this);
    m_drawObj = new DrawObject(this);

}

ImagePageViewer::~ImagePageViewer()
{
    delete ui;
}

void ImagePageViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    QRect clientRc(0, 0, width(), height());
    painter.begin(this);
    painter.fillRect(clientRc, QBrush(Qt::black));
    int l = 6;
    int t = 6;
    int n = 0;
    for (int i = 0; i < images.count(); i++)
    {

        QRect imgRc(l, t, 240, 240);
        painter.setPen(QColor(197, 197, 197));
        painter.setBrush(QColor(79, 79, 79));
        painter.drawRect(imgRc);
        ImageObject* cell = images.at(i);
        QPixmap pix;
        if (!cell->hasLoad())
        {
            cell->loadImage();


            n++;
        }
        pix = cell->pix();
        QRect innerRc(imgRc.left() + 2, imgRc.top() + 2, imgRc.width() - 4, imgRc.height() - 4);
        m_drawObj->drawPixmap(painter, innerRc, pix);







        l = l + imgRc.width() + 16;
        if ((l + imgRc.width()) > width())
        {
            l = 6;
            t += imgRc.height() + 24;
        }
        if (i == 48)
        {
            break;
        }

    }
    painter.end();
}

void ImagePageViewer::mouseMoveEvent(QMouseEvent* event)
{
    update();

}
