#include "apptabbar.h"
#include "ui_apptabbar.h"

AppTabBar::AppTabBar(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::AppTabBar)
{
    ui->setupUi(this);
    m_backgroundColor = QColor(202, 10, 30);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);

}

AppTabBar::~AppTabBar()
{
    delete ui;
}

void AppTabBar::addItem(QString caption, QString iconPath)
{

}

void AppTabBar::addItem(QString caption, QPixmap selectIcon, QPixmap defaultIcon)
{
    TabBarItem* item = new TabBarItem(this);
    item->setCapiton(caption);
    item->setIcon(defaultIcon);
    item->setSelectedIcon(selectIcon);
    item->setIndex(m_items.count());
    m_items.append(item);
    update();

}

void AppTabBar::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(rect(), QBrush(m_backgroundColor));


    int t = 32;
    qDebug() << m_items.count();
    for (int i = 0; i < m_items.count(); i++)
    {
        TabBarItem* item = m_items.at(i);
        QRect rc(0, t, width(), 64);
        QRect iconRc((width() - 24) / 2, t + 9, 24, 24);
        if (m_currentIndex == i)
        {
            painter.fillRect(rc, QBrush(QColor(194, 53, 45)));
            painter.drawPixmap(iconRc, item->selectedIcon());
        }
        else
        {
            painter.drawPixmap(iconRc, item->icon());
        }


        QRect textRc(0, t + 33, width(), 24);
        painter.setPen(Qt::white);
        painter.drawText(textRc, Qt::AlignCenter, item->capiton());
        item->setRect(rc);
        t += 64;

    }
    painter.end();

}

void AppTabBar::mousePressEvent(QMouseEvent* event)
{
    QPoint pt = m_helper->cursorPos();
    for (int i = 0; i < m_items.count(); i++)
    {
        TabBarItem* item = m_items.at(i);
        if (item->rect().contains(pt))
        {
            m_currentIndex = i;
            emit clickItem(item);
            update();
            break;
        }
    }

}

QColor AppTabBar::backgroundColor() const
{
    return m_backgroundColor;
}

void AppTabBar::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}

int AppTabBar::currentIndex() const
{
    return m_currentIndex;
}

void AppTabBar::setCurrentIndex(int newCurrentIndex)
{
    m_currentIndex = newCurrentIndex;
    for (int i = 0; i < m_items.count(); i++)
    {
        TabBarItem* item = m_items.at(i);
        item->setIsSelected(item->index() == m_currentIndex);
    }
    update();
}
