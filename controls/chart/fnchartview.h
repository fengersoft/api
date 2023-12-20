#ifndef FNCHARTVIEW_H
#define FNCHARTVIEW_H

#include <QObject>
#include "fnchartvalues.h"

class FnChartView : public QObject
{
    Q_OBJECT
public:
    explicit FnChartView(QObject* parent = nullptr);

    int index() const;
    void setIndex(int newIndex);

    FnChartValues* values() const;
    void setValues(FnChartValues* newValues);

    int minValue() const;
    void setMinValue(int newMinValue);

    int maxValue() const;
    void setMaxValue(int newMaxValue);

    QRect tagRect() const;
    void setTagRect(const QRect& newTagRect);

    QColor color() const;
    void setColor(const QColor& newColor);

    QString caption() const;
    void setCaption(const QString& newCaption);
    void clear();

signals:
private:
    FnChartValues* m_values;
    int m_index;
    int m_minValue;
    int m_maxValue;
    QRect m_tagRect;
    QColor m_color;
    QString m_caption;


};

#endif // FNCHARTVIEW_H
