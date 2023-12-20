#include "fnscrolllist.h"
#include "ui_fnscrolllist.h"

FnScrollList::FnScrollList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnScrollList)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(0);
    setMouseTracking(true);
}

FnScrollList::~FnScrollList()
{
    delete ui;
}

void FnScrollList::addItem(QString caption)
{
    FnListItem* item = new FnListItem(this);
    item->setCaption(caption);
    m_items << item;

    update();
}

void FnScrollList::addItemInHead(QString caption)
{
    FnListItem* item = new FnListItem(this);
    item->setCaption(caption);
    m_items.insert(0, item);
    m_helper->moveTop(0);

    update();

}

bool FnScrollList::existsItem(QString caption)
{
    for (int i = 0; i < m_items.count(); i++)
    {
        FnListItem* item = m_items.at(i);
        if (item->caption() == caption)
        {
            return true;
        }
    }

    return false;

}

void FnScrollList::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    int t = m_helper->itemsTop();
    for (int i = 0; i < m_items.count(); i++)
    {
        FnListItem* item = m_items.at(i);
        QRect rect(16, t, width() - 32, 24);
        item->setRect(rect);
        painter.drawText(rect, item->caption(), Qt::AlignLeft | Qt::AlignVCenter);
        t += 24;
    }
    painter.end();



}

void FnScrollList::wheelEvent(QWheelEvent* event)
{

}

void FnScrollList::mousePressEvent(QMouseEvent* event)
{
    m_helper->startMouseDown();

}

void FnScrollList::mouseReleaseEvent(QMouseEvent* event)
{
    m_helper->startMouseUp();

}

void FnScrollList::mouseMoveEvent(QMouseEvent* event)
{
    if (m_helper->mousedownFlag())
    {

        qDebug() << m_helper->mousedownPoint() << m_helper->cursorPos();
        int d = m_helper->cursorPos().y() - m_helper->mousedownPoint().y();
        qDebug() << d;
        m_helper->moveTop(d);
        m_helper->setMousedownPoint(m_helper->cursorPos());
    }


}
