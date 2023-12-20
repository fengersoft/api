#ifndef RINGCHART_H
#define RINGCHART_H

#include <QWidget>
#include <QPainter>

namespace Ui
{
class RingChart;
}

class RingChart : public QWidget
{
    Q_OBJECT

public:
    explicit RingChart(QWidget* parent = nullptr);
    ~RingChart();

    int minValue() const;
    void setMinValue(int newMinValue);

    int maxValue() const;
    void setMaxValue(int newMaxValue);

    double value() const;
    void setValue(double newValue);
    QColor borderColor() const;
    void setBorderColor(const QColor& newBorderColor);

    QString unit() const;
    void setUnit(const QString& newUnit);

    int fontSize() const;
    void setFontSize(int newFontSize);

protected:
    void paintEvent(QPaintEvent* event);
private:
    Ui::RingChart* ui;
    double m_value;
    int m_minValue;
    int m_maxValue;
    QColor m_borderColor;
    QString m_unit;
    int m_fontSize;
};

#endif // RINGCHART_H
