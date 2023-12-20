#include "colortoolbar.h"
#include "colortoolbarbutton.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qnamespace.h"
#include "qpoint.h"
#include "qwindowdefs.h"
#include "ui_colortoolbar.h"

ColorToolbar::ColorToolbar(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ColorToolbar)
{
    ui->setupUi(this);
    m_backgroundColor = QColor(60, 60, 60);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);
}

ColorToolbar::~ColorToolbar()
{
    delete ui;
}

const QColor& ColorToolbar::backgroundColor() const
{
    return m_backgroundColor;
}

void ColorToolbar::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
}

int ColorToolbar::selectedIndex() const
{
    return m_selectedIndex;
}

void ColorToolbar::setSelectedIndex(int newSelectedIndex)
{
    m_selectedIndex = newSelectedIndex;
}

void ColorToolbar::addDefaultColorButtons()
{
    QColor colors[] {QColor(0, 0, 0), QColor(128, 128, 128), QColor(255, 255, 255),
                     QColor(255, 0, 0), QColor(255, 165, 0), QColor(255, 255, 0),
                     QColor(0, 255, 0), QColor(0, 255, 255), QColor(0, 0, 255), QColor(128, 0, 128)
                    };
    for (int i = 0; i < 10; i++)
    {
        addColor(colors[i]);
    }


}

void ColorToolbar::addColor(QColor color)
{
    ColorToolbarButton* btn = new ColorToolbarButton(this);
    btn->setColor(color);
    btn->setIndex(m_buttons.count());
    m_buttons << btn;
    update();

}

QColor ColorToolbar::selectColor()
{
    if ((m_selectedIndex<0) || (m_selectedIndex>(m_buttons.count()-1)))
    {
        return QColor(0,0,0,0);
    }else
    {
        return m_buttons.at(m_selectedIndex)->color();
    }

}

void ColorToolbar::paintEvent(QPaintEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    QRect clientRc = m_helper->clientRect();
    painter.fillRect(clientRc, QBrush(m_backgroundColor));
    int t = (height() - 24) / 2;
    int l = 16;
    for (int i = 0; i < m_buttons.count(); i++)
    {
        ColorToolbarButton* btn = m_buttons.at(i);
        QRect btnRc(l, t, 24, 24);
        btn->setRect(btnRc);
        painter.setPen(btn->color().darker());
        if ((btnRc.contains(curPt)) || (btn->selected()))
        {
            painter.setBrush(Qt::NoBrush);
            QRect borderRc(l - 2, t - 2, 28, 28);
            painter.drawRect(borderRc);
        }

        painter.setBrush(btn->color());
        if (btn->selected())
        {
            QRect btnInnerRc(l + 2, t + 2, 20, 20);
            painter.drawRect(btnInnerRc);
        }
        else
        {
            painter.drawRect(btnRc);
        }



        l += 40;
    }

    painter.end();


}

void ColorToolbar::mouseMoveEvent(QMouseEvent* event)
{
    update();

}

void ColorToolbar::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();
    for (ColorToolbarButton* btn : m_buttons)
    {
        if (btn->rect().contains(curPt))
        {
            m_selectedIndex=btn->index();
            btn->setSelected(true);
            emit clickToolbarButton(btn);
        }
        else
        {
            btn->setSelected(false);
        }
    }
    update();

}
