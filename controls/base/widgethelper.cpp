#include "widgethelper.h"

WidgetHelper::WidgetHelper(QObject* parent) : QObject(parent)
{
    m_mousedownFlag = false;

}

bool WidgetHelper::mousedownFlag() const
{
    return m_mousedownFlag;
}

void WidgetHelper::setMousedownFlag(bool mousedownFlag)
{
    m_mousedownFlag = mousedownFlag;
    m_control->update();
}

QPoint WidgetHelper::mousedownPoint() const
{
    return m_mousedownPoint;
}

void WidgetHelper::setMousedownPoint(const QPoint& mousedownPoint)
{
    m_mousedownPoint = mousedownPoint;
}

void WidgetHelper::startMouseDown()
{
    m_mousedownFlag = true;
    m_mousedownPoint = m_control->cursor().pos();
    m_mousedownPoint = m_control->mapFromGlobal(m_mousedownPoint);


}

void WidgetHelper::startMouseUp()
{
    m_mousedownFlag = false;
}

void WidgetHelper::mouseMove(int& x, int& y)
{
    QPoint pt = m_control->cursor().pos();
    pt = m_control->mapFromGlobal(pt);
    x = pt.x() - m_mousedownPoint.x();
    y = pt.y() - m_mousedownPoint.y();
    m_mousedownPoint = pt;

}

QWidget* WidgetHelper::control() const
{
    return m_control;
}

void WidgetHelper::setControl(QWidget* control)
{
    m_control = control;
}

QPoint WidgetHelper::cursorPos()
{
    QPoint pt = m_control->cursor().pos();
    pt = m_control->mapFromGlobal(pt);
    return pt;
}
