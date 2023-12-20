#include "pageswidget.h"
#include "pagebutton.h"
#include "qalgorithms.h"
#include "qfontmetrics.h"
#include "qnamespace.h"
#include "qwindowdefs.h"
#include "ui_pageswidget.h"

pagesWidget::pagesWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::pagesWidget)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setMaxLeft(6);
    m_helper->setItemsLeft(6);
}

pagesWidget::~pagesWidget()
{
    delete ui;
}

int pagesWidget::pageCount() const
{
    return m_pageCount;
}

void pagesWidget::setPageCount(int newPageCount)
{
    m_pageCount = newPageCount;
    qDeleteAll(m_buttons);
    m_buttons.clear();
    for (int i = 1; i <= m_pageCount; i++)
    {
        PageButton* btn = new PageButton(this);
        btn->setCaption(QString("%1").arg(i));
        m_buttons << btn;
    }
    update();
}

void pagesWidget::paintEvent(QPaintEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    int l = m_helper->itemsLeft();
    int t = (height() - 22) / 2;
    QFontMetrics fm = painter.fontMetrics();
    for (int i = 0; i < m_buttons.count(); i++)
    {
        PageButton* btn = m_buttons.at(i);
        QRect btnRc(l, t, fm.boundingRect(btn->caption()).width() + 24, 22);
        btn->setRect(btnRc);

        QPen pen = painter.pen();
        pen.setWidthF(0.5);
        if (btnRc.contains(curPt))
        {
            pen.setColor(QColor(0, 120, 212));
            painter.setBrush(QBrush(QColor(224, 238, 249)));
        }
        else
        {
            pen.setColor(QColor(208, 208, 208));
            painter.setBrush(QBrush(QColor(253, 253, 253)));
        }
        painter.setPen(pen);
        painter.drawRect(btnRc);
        painter.setPen(Qt::black);
        painter.drawText(btnRc, Qt::AlignCenter, btn->caption());
        l += btn->rect().width() + 6;
    }
    painter.end();

}

void pagesWidget::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void pagesWidget::wheelEvent(QWheelEvent* event)
{

    m_helper->moveLeft(event->angleDelta().y());
    update();

}

void pagesWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_buttons.count(); i++)
    {
        PageButton* btn = m_buttons.at(i);
        if (btn->rect().contains(curPt))
        {
            emit getPageNum(btn->caption().toInt());
            break;
        }

    }

}
