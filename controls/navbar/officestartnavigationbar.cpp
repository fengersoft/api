#include "officestartnavigationbar.h"
#include "ui_officestartnavigationbar.h"

OfficeStartNavigationBar::OfficeStartNavigationBar(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::OfficeStartNavigationBar)
{
    //推荐宽度140
    ui->setupUi(this);
    m_backgroundColor = QColor(43, 87, 154);
    m_selectColor = QColor(0, 32, 80);
    m_hotColor = QColor(18, 64, 120);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);

}

OfficeStartNavigationBar::~OfficeStartNavigationBar()
{
    delete ui;
}

const QColor& OfficeStartNavigationBar::backgroundColor() const
{
    return m_backgroundColor;
}

void OfficeStartNavigationBar::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}

void OfficeStartNavigationBar::addIconButton(QString caption, QString imagePath)
{
    BaseItem* item = new BaseItem(this);
    item->setCaption(caption);
    item->setIcon(QPixmap(imagePath));
    item->setIndex(m_iconButtons.count());
    m_iconButtons << item;
    update();

}

void OfficeStartNavigationBar::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QRect clientRect = m_helper->clientRect();
    QPoint curPt = m_helper->cursorPos();
    painter.fillRect(clientRect, QBrush(m_backgroundColor));

    int t = 84;
    int w = width();
    int h = w;
    for (int i = 0; i < m_iconButtons.count(); i++)
    {
        BaseItem* item = m_iconButtons.at(i);
        QRect itemRc = QRect(0, t, w, h);
        item->setRect(itemRc);

        if (itemRc.contains(curPt))
        {
            painter.fillRect(itemRc, QBrush(m_hotColor));
        }
        else if (item->selected())
        {
            painter.fillRect(itemRc, QBrush(m_selectColor));

        }


        int l = (w - 32) / 2;
        QRect iconRc = QRect(l, t + l - 16, 32, 32);
        painter.drawPixmap(iconRc, item->icon(), item->icon().rect());

        QRect textRc = QRect(0, t + l + 24, w, 24);
        painter.setPen(Qt::white);
        painter.drawText(textRc, Qt::AlignCenter, item->caption());

        t += h;

    }


    painter.end();

}

void OfficeStartNavigationBar::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void OfficeStartNavigationBar::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    BaseItem* selItem = getSelectIconButton();
    if (selItem == nullptr)
    {
        return;
    }
    for (BaseItem* item : m_iconButtons)
    {
        if (item->rect().contains(curPt))
        {
            item->setSelected(true);
            emit clickIconButton(item);
        }
        else
        {
            item->setSelected(false);
        }
    }

    update();

}

const QColor& OfficeStartNavigationBar::hotColor() const
{
    return m_hotColor;
}

void OfficeStartNavigationBar::setHotColor(const QColor& newHotColor)
{
    m_hotColor = newHotColor;
}

BaseItem* OfficeStartNavigationBar::getSelectIconButton()
{
    QPoint curPt = m_helper->cursorPos();
    BaseItem* selItem = nullptr;
    for (BaseItem* item : m_iconButtons)
    {
        if (item->rect().contains(curPt))
        {
            selItem = item;
        }
    }

    return selItem;

}

const QString& OfficeStartNavigationBar::caption() const
{
    return m_caption;
}

void OfficeStartNavigationBar::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
}

const QColor& OfficeStartNavigationBar::selectColor() const
{
    return m_selectColor;
}

void OfficeStartNavigationBar::setSelectColor(const QColor& newSelectColor)
{
    m_selectColor = newSelectColor;
}

BaseItem* OfficeStartNavigationBar::iconButton(int index)
{
    return m_iconButtons.at(index);

}
