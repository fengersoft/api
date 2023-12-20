#include "floatwindow.h"
#include "ui_floatwindow.h"

FloatWindow::FloatWindow(QWidget* parent) :
    AbstractFloatWindow(parent),
    ui(new Ui::FloatWindow)
{
    ui->setupUi(this);
}

FloatWindow::~FloatWindow()
{
    delete ui;
}

void FloatWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
#if (QT_VERSION<QT_VERSION_CHECK(6,0,0))
    painter.setRenderHints(QPainter::HighQualityAntialiasing);
#else
    painter.setRenderHints(QPainter::Antialiasing);
#endif
    painter.setBrush(QColor(237, 247, 255));
    painter.setPen(QColor(6, 167, 255));
    QRect toolbarRc(8, 16, width() - 8, 32);
    painter.drawRoundedRect(toolbarRc, 16, 16);
    QRect iconBorderRc(0, 8, 48, 48);
    painter.drawEllipse(iconBorderRc);

    QRect iconRc(8, 16, 32, 32);
    painter.drawPixmap(iconRc, m_icon, m_icon.rect());

    //绘制按钮
    int buttonLeft = 64;
    QFontMetrics fm = painter.fontMetrics();
    for (int i = 0; i < m_items.count(); i++)
    {
        BaseItem* item = m_items.at(i);
#if(QT_VERSION<QT_VERSION_CHECK(6,0,0))
        int w = fm.width(item->caption()) + 12;
#else
        int w = fm.maxWidth() * item->caption().size() + 12;
#endif
        QRect btnRc(buttonLeft, 20, w, 24);
        painter.drawText(btnRc, Qt::AlignCenter, item->caption());

        item->setRect(btnRc);
        if (i != (m_items.count() - 1))
        {
            painter.drawLine(buttonLeft + w + 3, 26, buttonLeft + w + 3, 38);
        }
        buttonLeft += (w + 6);


    }

    painter.end();

}

void FloatWindow::mousePressEvent(QMouseEvent* event)
{

    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        BaseItem* item = m_items.at(i);
        if (item->rect().contains(pt))
        {
            emit clickItem(item);
            return;
        }
    }
    AbstractFloatWindow::mousePressEvent(event);

}

const QList<BaseItem*>& FloatWindow::items() const
{
    return m_items;
}

void FloatWindow::setItems(const QList<BaseItem*>& newItems)
{
    m_items = newItems;
}

void FloatWindow::addItem(QString caption)
{
    BaseItem* item = new BaseItem(this);
    item->setCaption(caption);

    m_items << item;
    update();

}

const QPixmap& FloatWindow::icon() const
{
    return m_icon;
}

void FloatWindow::setIcon(const QPixmap& newIcon)
{
    m_icon = newIcon;
    update();
}
