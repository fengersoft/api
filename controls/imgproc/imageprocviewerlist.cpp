#include "imageprocviewerlist.h"
#include "ui_imageprocviewerlist.h"

ImageProcViewerList::ImageProcViewerList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ImageProcViewerList)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    selObj = nullptr;
    m_scrollBar = new VerticalScrollBar(this);
    m_scrollBar->setControl(this);
    setMouseTracking(true);
}

ImageProcViewerList::~ImageProcViewerList()
{
    delete ui;
}

void ImageProcViewerList::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(QColor(113, 113, 113)));
    int t = m_helper->itemsTop();
    for (int i = 0; i < procHistoryList.count(); i++)
    {
        ImageProcHistoryObject* obj = procHistoryList.at(i);
        obj->setRect(QRect(16, t, 128, obj->showPix.height()));
        if (selObj == obj)
        {
            QRect selRect(14, t - 2, width() - 30, 132);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(Qt::white);
            painter.drawRect(selRect);
        }
        painter.drawPixmap(obj->rect(), obj->showPix, obj->showPix.rect());
        t = t + 128 + 16;

    }
    m_scrollBar->setMaxValue(procHistoryList.count() * 144 - height());
    m_scrollBar->setValue(-m_helper->itemsTop());

    m_scrollBar->setMaxValue(t);
    m_scrollBar->setValue(-m_helper->itemsTop());
    m_scrollBar->drawScrollBar(painter);
    painter.end();


}

void ImageProcViewerList::mousePressEvent(QMouseEvent* event)
{
    m_helper->startMouseDown();
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < procHistoryList.count(); i++)
    {
        ImageProcHistoryObject* obj = procHistoryList.at(i);
        if (obj->rect().contains(curPt))
        {
            selObj = obj;
            break;
        }
    }
    m_scrollBar->startMouseDown();
    update();

}

void ImageProcViewerList::mouseReleaseEvent(QMouseEvent* event)
{
    m_helper->startMouseUp();
    m_scrollBar->startMouseUp();
    update();

}

void ImageProcViewerList::mouseDoubleClickEvent(QMouseEvent* event)
{

}

void ImageProcViewerList::mouseMoveEvent(QMouseEvent* event)
{
    m_scrollBar->moveButton(m_helper);



}

void ImageProcViewerList::wheelEvent(QWheelEvent* event)
{
    int y = event->angleDelta().y();
    m_helper->moveTop(y);

}
