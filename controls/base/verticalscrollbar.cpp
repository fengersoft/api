#include "verticalscrollbar.h"

VerticalScrollBar::VerticalScrollBar(QObject* parent)
    : QObject{parent}
{
    m_drawObj = new DrawObject(this);
    m_minValue = 0;


}

int VerticalScrollBar::minValue() const
{
    return m_minValue;
}

void VerticalScrollBar::setMinValue(int newMinValue)
{
    m_minValue = newMinValue;
}

int VerticalScrollBar::value() const
{
    return m_value;
}

void VerticalScrollBar::setValue(int newValue)
{
    m_value = newValue;
}

int VerticalScrollBar::maxValue() const
{
    return m_maxValue;
}

void VerticalScrollBar::setMaxValue(int newMaxValue)
{
    m_maxValue = newMaxValue;
}

void VerticalScrollBar::drawScrollBar(QPainter& painter, QRect drawRect)
{
    QPoint curPt = m_control->mapFromGlobal(m_control->cursor().pos());
    int clientHeight = drawRect.height() - 48;
    painter.save();
    painter.fillRect(drawRect, QBrush(QColor(230, 230, 230)));
    m_upButtonRect = QRect(drawRect.left(), drawRect.top(), 16, 16);

    m_drawObj->drawTriangleButton(painter, m_upButtonRect, QColor(120, 120, 120), DrawTriUp, 2);

    m_downButtonRect = QRect(drawRect.left(), drawRect.bottom() - 16, 16, 16);
    m_drawObj->drawTriangleButton(painter, m_downButtonRect, QColor(120, 120, 120), DrawTriDown, 2);

    double d = m_value;
    d = d / (m_maxValue - m_minValue);

    int t = std::trunc(d * clientHeight) + 24;
    if (t >= (drawRect.height() - 24))
    {
        t = drawRect.height() - 24;
    }
    if (t < 24)
    {
        t = 24;
    }
    m_buttonRect = QRect(drawRect.left(), t - 8, 16, 16);
    if (m_buttonRect.contains(curPt))
    {
        painter.fillRect(m_buttonRect, QBrush(QColor(168, 168, 168)));
    }
    else
    {
        painter.fillRect(m_buttonRect, QBrush(QColor(193, 193, 193)));
    }

    painter.restore();

}

void VerticalScrollBar::drawScrollBar(QPainter& painter)
{
    QRect drawRc(m_control->width() - 16, 0, 16, m_control->height());
    drawScrollBar(painter, drawRc);

}

const QRect& VerticalScrollBar::buttonRect() const
{
    return m_buttonRect;
}

void VerticalScrollBar::setButtonRect(const QRect& newButtonRect)
{
    m_buttonRect = newButtonRect;
}

QWidget* VerticalScrollBar::control() const
{
    return m_control;
}

void VerticalScrollBar::setControl(QWidget* newControl)
{
    m_control = newControl;
}

bool VerticalScrollBar::isPointInButtonRect()
{
    QPoint curPt = m_control->cursor().pos();
    curPt = m_control->mapFromGlobal(curPt);
    return m_buttonRect.contains(curPt);

}

bool VerticalScrollBar::isPointInUpButtonRect()
{
    QPoint curPt = m_control->cursor().pos();
    curPt = m_control->mapFromGlobal(curPt);
    return m_upButtonRect.contains(curPt);

}

bool VerticalScrollBar::isPointInDownButtonRect()
{
    QPoint curPt = m_control->cursor().pos();
    curPt = m_control->mapFromGlobal(curPt);
    return m_downButtonRect.contains(curPt);

}

void VerticalScrollBar::startMouseDown()
{
    if (isPointInButtonRect())
    {
        m_buttonSelected = true;
    }
    else
    {
        m_buttonSelected = false;
    }
    qDebug() << m_buttonSelected;

}

void VerticalScrollBar::startMouseUp()
{
    m_buttonSelected = false;

}

bool VerticalScrollBar::buttonSelected() const
{
    return m_buttonSelected;
}

void VerticalScrollBar::setButtonSelected(bool newButtonSelected)
{
    m_buttonSelected = newButtonSelected;
}

void VerticalScrollBar::moveButtonPos(int d)
{
    qDebug() << "move";
    m_value += d * 100;

    m_control->update();

}

int VerticalScrollBar::maptoControlValue(int v)
{


    double d = m_control->height() - 48;
    d = d / (m_maxValue - m_minValue);

    return v / d;

}

void VerticalScrollBar::moveButton(WidgetHelper* helper)
{
    if (helper->mousedownFlag())
    {
        QPoint curPt = helper->cursorPos();
        int d = curPt.y() - helper->mouseMovePoint().y();
        if (buttonSelected())
        {
            d = maptoControlValue(d);
            if ((d > 0) && (!isValueInMaxBoundary()))
            {
                helper->moveTop(-d);
            }
            if (d < 0)
            {
                helper->moveTop(-d);
            }
        }

        helper->setMouseMovePoint(curPt);
    }

}

bool VerticalScrollBar::isValueInBoundary()
{
    if (m_value == 0)
    {
        return true;
    }
    if (m_value >= m_maxValue)
    {
        return true;
    }
    return false;

}

bool VerticalScrollBar::isValueInMaxBoundary()
{
    if (m_value >= m_maxValue)
    {
        return true;
    }
    return false;

}


