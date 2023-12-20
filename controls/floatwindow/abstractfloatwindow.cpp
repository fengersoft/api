#include "abstractfloatwindow.h"

AbstractFloatWindow::AbstractFloatWindow(QWidget *parent)
    : QWidget{parent}
{

    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint|Qt::SubWindow);
    setMaximumHeight(64);
    setMinimumHeight(64);
    m_helper=new WidgetHelper(this);
    m_helper->setControl(this);
    setContextMenuPolicy(Qt::ActionsContextMenu);
    setAttribute(Qt::WA_TranslucentBackground);
    QStringList menuNames;
    menuNames<<"隐藏";
    for(int i=0;i<menuNames.count();i++)
    {
        QAction *act=new QAction(this);
        act->setText(menuNames[i]);
        connect(act,&QAction::triggered,this,&AbstractFloatWindow::onTriggered);
        addAction(act);

    }

}

void AbstractFloatWindow::mousePressEvent(QMouseEvent *event)
{
    m_helper->startMouseDown();

}

void AbstractFloatWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_helper->startMouseUp();

}

void AbstractFloatWindow::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void AbstractFloatWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (m_helper->mousedownFlag())
    {
        QPoint pt=this->cursor().pos();
        int dx=pt.x()-m_helper->globalMousedownPoint().x();
        int dy=pt.y()-m_helper->globalMousedownPoint().y();
        move(this->x()+dx,this->y()+dy);
        m_helper->setGlobalMousedownPoint(pt);

    }


}

void AbstractFloatWindow::onTriggered()
{
    QAction *act=static_cast<QAction*>(sender());
    if (act->text()=="隐藏")
    {
        hide();
    }

}
