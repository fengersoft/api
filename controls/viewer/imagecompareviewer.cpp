#include "imagecompareviewer.h"
#include "qaction.h"
#include "qmenu.h"
#include "qnamespace.h"
#include "qpoint.h"
#include "qwindowdefs.h"
#include "ui_imagecompareviewer.h"
#include <algorithm>

ImageCompareViewer::ImageCompareViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ImageCompareViewer)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_drawObj = new DrawObject(this);
    m_helper->setZoomFactor(1.0);


}

ImageCompareViewer::~ImageCompareViewer()
{
    delete ui;
}

void ImageCompareViewer::addFile(QString pathName)
{
    QPixmap pix = QPixmap(pathName);
    ImageObject* obj = new ImageObject(this);
    obj->setPath(pathName);
    obj->setPix(pix);
    m_images << obj;
    update();



}

void ImageCompareViewer::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect clientRc = QRect(m_helper->startLeft(), m_helper->startTop(),
                           m_helper->zoomFactor() * width(),
                           m_helper->zoomFactor() * height());
    int clientWidth = clientRc.width();
    int clientHeight = clientRc.height();

    painter.fillRect(clientRc, QColor(97, 97, 97));
    if (m_images.count() == 0)
    {

    }
    else if (m_images.count() == 1)
    {
        ImageObject* obj = m_images.at(0);
        QPixmap pix = obj->pix();
        m_drawObj->drawPixmap(painter, clientRc, pix);


    }
    else if (m_images.count() <= 3)
    {
        int w = clientWidth / m_images.count();
        for (int i = 0; i < m_images.count(); i++)
        {
            ImageObject* obj = m_images.at(i);
            QPixmap pix = obj->pix();
            QRect rc(m_helper->startLeft() + i * w, m_helper->startTop() + 0, w, clientHeight);
            m_drawObj->drawPixmap(painter, rc, pix);
            painter.setPen(QColor(117, 117, 117));
            painter.drawLine(m_helper->startLeft() + (i + 1)*w, m_helper->startTop() + 0,
                             m_helper->startLeft() + (i + 1)*w, m_helper->startTop() + clientHeight);
        }
    }
    else
    {
        int w, h;
        if (clientWidth < clientHeight)
        {
            w = clientWidth / 2;


            h = clientHeight / (m_images.count() / 2) ;
        }
        else
        {
            h = clientHeight / 2;


            w = clientWidth / (m_images.count() / 2) ;

        }

        for (int i = 0; i < m_images.count(); i++)
        {
            ImageObject* obj = m_images.at(i);
            QPixmap pix = obj->pix();
            QRect rc;
            if (clientHeight > clientWidth)
            {
                rc = QRect(m_helper->startLeft() + (i % 2) * w, m_helper->startTop() + (i / 2) * h, w, h);
            }
            else
            {
                int n = qCeil(m_images.count() / 2);

                rc = QRect(m_helper->startLeft() + (i % n) * w, m_helper->startTop() + (i / (m_images.count() / 2)) * h, w, h);
            }

            qDebug() << i << rc;

            m_drawObj->drawPixmap(painter, rc, pix);
            painter.setPen(QColor(117, 117, 117));
            painter.drawRect(rc);
        }
    }
    painter.end();

}

void ImageCompareViewer::wheelEvent(QWheelEvent* event)
{
    double d = event->angleDelta().y();
    if (d > 0)
    {
        m_helper->setZoomFactor(m_helper->zoomFactor() * 1.1);
    }
    else
    {
        m_helper->setZoomFactor(m_helper->zoomFactor() * 0.8);
    }
    update();

}

void ImageCompareViewer::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::RightButton)
    {
        QMenu* menu = new QMenu(this);
        QStringList menuNames;
        menuNames << "顺序反转";
        for (int i = 0; i < menuNames.count(); i++)
        {
            QAction* act = new QAction(this);
            act->setText(menuNames[i]);
            menu->addAction(act);
            connect(act, &QAction::triggered, this, &ImageCompareViewer::onRightMenuTriggered);
        }

        menu->exec(cursor().pos());

        delete menu;
        return;

    }
    m_helper->startMouseDown();

}

void ImageCompareViewer::mouseReleaseEvent(QMouseEvent* event)
{
    m_helper->startMouseUp();

}

void ImageCompareViewer::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint pt = m_helper->cursorPos();
        int x = pt.x() - m_helper->mouseMovePoint().x();
        int y = pt.y() - m_helper->mouseMovePoint().y();
        m_helper->setStartLeft(m_helper->startLeft() + x);
        m_helper->setStartTop(m_helper->startTop() + y);
        m_helper->setMouseMovePoint(pt);
        update();

    }

}

void ImageCompareViewer::onRightMenuTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    if (act->text() == "顺序反转")
    {
        std::reverse(m_images.begin(), m_images.end());
        update();
    }
}


