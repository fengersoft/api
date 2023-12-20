#include "ringchart.h"
#include "ui_ringchart.h"

RingChart::RingChart(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RingChart)
{
    ui->setupUi(this);
    m_minValue = -20;
    m_maxValue = 60;
    m_value = 24;
    m_borderColor = Qt::darkBlue;
    m_unit = "℃";
    m_fontSize = 42;
}

RingChart::~RingChart()
{
    delete ui;
}

int RingChart::minValue() const
{
    return m_minValue;
}

void RingChart::setMinValue(int newMinValue)
{
    m_minValue = newMinValue;
}

int RingChart::maxValue() const
{
    return m_maxValue;
}

void RingChart::setMaxValue(int newMaxValue)
{
    m_maxValue = newMaxValue;
}

double RingChart::value() const
{
    return m_value;
}

void RingChart::setValue(double newValue)
{
    m_value = newValue;
    update();
}

void RingChart::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter;
    painter.begin(this);
    QPen pen = painter.pen();
    pen.setColor(m_borderColor);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setRenderHints(QPainter::Antialiasing);
    int n = width() < height() ? width() : height();
    n = n - 64;
    QRect rect((width() - n) / 2, (height() - n) / 2, n, n);
    int d = std::trunc(360 * (m_value - m_minValue) / (m_maxValue - m_minValue));
    painter.drawArc(rect, 90 * 16, -d * 16);
    QFont font = painter.font();
    font.setPixelSize(m_fontSize);
    painter.setFont(font);
    QString s = QString("%1 %2").arg(m_value).arg(m_unit);
    painter.drawText(rect, Qt::AlignCenter, s);
    painter.end();

}

int RingChart::fontSize() const
{
    return m_fontSize;
}

void RingChart::setFontSize(int newFontSize)
{
    m_fontSize = newFontSize;
}

QString RingChart::unit() const
{
    return m_unit;
}

void RingChart::setUnit(const QString& newUnit)
{
    m_unit = newUnit;
}

QColor RingChart::borderColor() const
{
    return m_borderColor;
}

void RingChart::setBorderColor(const QColor& newBorderColor)
{
    m_borderColor = newBorderColor;
}
