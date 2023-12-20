#ifndef FNCHARTYVALUE_H
#define FNCHARTYVALUE_H

#include <QObject>
#include <QPoint>
#include <QDebug>

class FnChartYValue : public QObject
{
    Q_OBJECT
public:
    explicit FnChartYValue(QObject* parent = nullptr);

    double value() const;
    void setValue(double value);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    QString caption() const;
    void setCaption(const QString& caption);
    QPoint point();

signals:

private:
    double m_value;
    int m_x;
    int m_y;
    QString m_caption;

};

#endif // FNCHARTYVALUE_H
