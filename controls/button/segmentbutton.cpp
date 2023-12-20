#include "segmentbutton.h"
#include "ui_segmentbutton.h"

SegmentButton::SegmentButton(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SegmentButton)
{
    ui->setupUi(this);
    m_drawObj = new DrawObject(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
}

SegmentButton::~SegmentButton()
{
    delete ui;
}

void SegmentButton::addButton(QString caption)
{
    ButtonItem* item = new ButtonItem(this);
    item->setCaption(caption);
    item->setBackgroundColor(Qt::white);
    item->setIndex(m_items.count());
    m_items << item;
    update();

}

ButtonItem* SegmentButton::item(int index)
{
    return m_items.at(index);

}

void SegmentButton::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing);


    int l = 1;
    for (int i = 0; i < m_items.count(); i++)
    {

        ButtonItem* item = m_items.at(i);
        QFont font = painter.font();
        font.setPixelSize(item->fontSize());
        painter.setFont(font);

        QFontMetrics fm = painter.fontMetrics();
        int w = fm.boundingRect(item->caption()).width() + 32;
        QRect rc(l, 1, w, height() - 2);
        if (i == 0)
        {
            m_drawObj->drawRoundedRect(painter, rc, item->color(), item->borderColor(), item->backgroundColor(),
                                       true, true, false, false, 8, 8);
        }
        else if (i == (m_items.count() - 1))
        {
            m_drawObj->drawRoundedRect(painter, rc, item->color(), item->borderColor(), item->backgroundColor(),
                                       false, false, true, true, 8, 8);

        }
        else
        {
            m_drawObj->drawRoundedRect(painter, rc, item->color(), item->borderColor(), item->backgroundColor(),
                                       false, false, false, false, 8, 8);
        }
        painter.setPen(item->color());
        painter.drawText(rc, Qt::AlignCenter, item->caption());
        item->setRect(rc);
        l += (w);
    }

    painter.end();

}

void SegmentButton::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        ButtonItem* item = m_items.at(i);
        QRect rc = item->rect();
        if (rc.contains(pt))
        {
            emit clickItem(item);
        }
    }


}
