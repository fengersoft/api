#include "dropdownbutton.h"
#include "ui_dropdownbutton.h"

DropDownButton::DropDownButton(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::DropDownButton)
{
    ui->setupUi(this);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    m_draw = new DrawObject(this);
    setMouseTracking(true);

}

DropDownButton::~DropDownButton()
{
    delete ui;
}

void DropDownButton::paintEvent(QPaintEvent* event)
{

    QRect clientRect = m_helper->clientRect();
    QPoint curPt = m_helper->cursorPos();
    QStyleOptionButton option;
    option.initFrom(this);
    if (clientRect.contains(curPt))
    {
        option.state |= QStyle::State_MouseOver;
    }
    else
    {
        option.state |= QStyle::State_Raised;
    }

    QPainter painter;
    painter.begin(this);
    style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

    painter.setPen(QColor(197, 197, 197));
    painter.drawLine(width() - height(), 4, width() - height(), height() - 4);

    m_arrowRect = QRect(width() - height(), 0, height(), height());
    m_draw->drawTriangleButton(painter, m_arrowRect, QColor(97, 97, 97), DrawTriDownV2, 9);
    QRect textRc(0, 0, width() - height(), height());
    painter.setPen(QColor(0, 0, 0));
    painter.drawText(textRc, Qt::AlignCenter, m_caption);

    painter.end();



}

void DropDownButton::mouseMoveEvent(QMouseEvent* event)
{
    update();
}

void DropDownButton::leaveEvent(QEvent* event)
{
    update();

}

void DropDownButton::mousePressEvent(QMouseEvent* event)
{
    QPoint curPt = m_helper->cursorPos();

    if (m_arrowRect.contains(curPt))
    {

        QMenu* menu = new QMenu();

        for (int i = 0; i < m_dropDownList.count(); i++)
        {
            QAction* act = new QAction();
            act->setText(m_dropDownList[i]);
            connect(act, &QAction::triggered, this, &DropDownButton::onActionTriggered);
            menu->addAction(act);
        }
        menu->setMinimumWidth(width());
        curPt = QPoint(0, height());
        curPt = mapToGlobal(curPt);
        menu->exec(curPt);
        delete menu;
    }

}

const QString& DropDownButton::caption() const
{
    return m_caption;
}

void DropDownButton::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
}

const QStringList& DropDownButton::dropDownList() const
{
    return m_dropDownList;
}

void DropDownButton::setDropDownList(const QStringList& newDropDownList)
{
    m_dropDownList = newDropDownList;
}

void DropDownButton::onActionTriggered()
{
    QAction* act = static_cast<QAction*>(sender());
    m_caption = act->text();
    update();

}
