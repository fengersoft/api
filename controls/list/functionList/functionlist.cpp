#include "functionlist.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qdebug.h"
#include "qnamespace.h"
#include "qpainter.h"
#include "qpoint.h"
#include "ui_functionlist.h"

FunctionList::FunctionList(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FunctionList)
{
    ui->setupUi(this);
    m_list = new RecommendList(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);

}

FunctionList::~FunctionList()
{
    delete ui;
}

void FunctionList::addItem(QString itemName)
{
    m_list->addItem(itemName);
    update();
}

void FunctionList::showAll()
{
    m_list->showAll();

    update();

}

void FunctionList::search(QString keyword)
{
    m_list->search(keyword);
    update();

}

void FunctionList::paintEvent(QPaintEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(QColor(255, 255, 255)));


    int t = 16;
    for (int i = 0; i < m_list->showList.count(); i++)
    {
        RecommendObject* item = m_list->showList.at(i);
        QRect textRc(16, t, width(), 32);
        QRect rc(0, t, width(), 32);
        if (rc.contains(curPt))
        {
            painter.fillRect(rc, QBrush(QColor(230, 230, 230)));
        }
        else
        {
            painter.fillRect(rc, QBrush(QColor(255, 255, 255)));
        }

        item->setRect(rc);
        QFont font = painter.font();
        font.setPixelSize(12);
        painter.setFont(font);
        painter.setPen(Qt::black);
        painter.drawText(textRc, item->name(), Qt::AlignLeft | Qt::AlignVCenter);
        t += 32;
        if ((i == 2) || (i == 5))
        {
            painter.setPen(QColor(200, 200, 200));
            painter.drawLine(0, t, width(), t);
        }

    }
    painter.end();

}

void FunctionList::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void FunctionList::mousePressEvent(QMouseEvent* event)
{

    QPoint curPt = m_helper->cursorPos();

    for (int i = 0; i < m_list->showList.count(); i++)
    {
        RecommendObject* item = m_list->showList.at(i);
        if (item->rect().contains(curPt))
        {
            qDebug() << item->name();
            item->incSelectedCount();
            break;
        }


    }



    update();


}

void FunctionList::leaveEvent(QEvent* event)
{
    m_list->smartByReSetOrder();
    update();
}
