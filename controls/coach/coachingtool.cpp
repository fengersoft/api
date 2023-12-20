#include "coachingtool.h"

CoachingTool::CoachingTool(QWidget* parent)
    : QWidget{parent}
{

    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);
    setMouseTracking(true);

}

const QString& CoachingTool::caption() const
{
    return m_caption;
}

void CoachingTool::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
}


