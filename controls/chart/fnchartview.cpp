#include "fnchartview.h"

FnChartView::FnChartView(QObject* parent)
    : QObject{parent}
{
    m_values = new FnChartValues(this);

}

int FnChartView::index() const
{
    return m_index;
}

void FnChartView::setIndex(int newIndex)
{
    m_index = newIndex;
}

FnChartValues* FnChartView::values() const
{
    return m_values;
}

void FnChartView::setValues(FnChartValues* newValues)
{
    m_values = newValues;
}

int FnChartView::minValue() const
{
    return m_minValue;
}

void FnChartView::setMinValue(int newMinValue)
{
    m_minValue = newMinValue;
}

int FnChartView::maxValue() const
{
    return m_maxValue;
}

void FnChartView::setMaxValue(int newMaxValue)
{
    m_maxValue = newMaxValue;
}

QRect FnChartView::tagRect() const
{
    return m_tagRect;
}

void FnChartView::setTagRect(const QRect& newTagRect)
{
    m_tagRect = newTagRect;
}

QColor FnChartView::color() const
{
    return m_color;
}

void FnChartView::setColor(const QColor& newColor)
{
    m_color = newColor;
}

QString FnChartView::caption() const
{
    return m_caption;
}

void FnChartView::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
}

void FnChartView::clear()
{
    qDeleteAll(m_values->values);
    m_values->values.clear();

}
