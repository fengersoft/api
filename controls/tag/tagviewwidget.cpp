#include "tagviewwidget.h"
#include "ui_tagviewwidget.h"

TagViewWidget::TagViewWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::TagViewWidget)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);
}

TagViewWidget::~TagViewWidget()
{
    delete ui;
}

void TagViewWidget::addItem(int id, QString caption)
{
    TagViewItem* item = new TagViewItem(this);
    item->setCaption(caption);
    item->setId(id);
    item->setBackgroundColor(ColorTable::getRandomColor());
    m_items << item;
    update();
}

void TagViewWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    QPoint curPt = m_helper->cursorPos();

    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    int l = 16;
    int t = 16;
    QFontMetrics fm = painter.fontMetrics();
    for (int i = 0; i < m_items.count(); i++)
    {
        TagViewItem* item = m_items.at(i);
        QRect rc = fm.boundingRect(item->caption());
        int w = rc.width() + 32;
        if ((l + w + 16) > width())
        {
            l = 16;
            t += rc.height() + 12 + 16;
        }
        painter.setPen(Qt::NoPen);

        QRect textRc(l, t, w, rc.height() + 12);
        QColor brColor = textRc.contains(curPt) ? item->backgroundColor().darker() :
                         item->backgroundColor();
        painter.setBrush(brColor);
        painter.drawRoundedRect(textRc, 16, 16);
        painter.setPen(Qt::white);
        painter.drawText(textRc, Qt::AlignCenter, item->caption());
        item->setRect(textRc);
        l += w + 16;





    }
    painter.end();

}

void TagViewWidget::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void TagViewWidget::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        TagViewItem* item = m_items.at(i);
        if (item->rect().contains(curPt))
        {
            if (event->button() == Qt::LeftButton)
            {
                emit clickItem(item);
            }
            else
            {
                QMenu* menu = new QMenu(this);
                QStringList menuNames;
                menuNames << "复制文字" << "新增" << "删除";
                for (int j = 0; j < menuNames.count(); j++)
                {
                    QAction* act = new QAction(menu);
                    act->setText(menuNames[j]);
                    menu->addAction(act);
                }
                QPoint pt(item->rect().left() + 8, item->rect().bottom());
                pt = this->mapToGlobal(pt);
                menu->exec(pt);
                delete menu;
            }

        }
    }
    update();

}
