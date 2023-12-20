#ifndef BALANCEWHEELITEM_H
#define BALANCEWHEELITEM_H

#include <QObject>
#include <QColor>

class BalanceWheelItem : public QObject
{
    Q_OBJECT
public:
    explicit BalanceWheelItem(QObject *parent = nullptr);

    double startAngle() const;
    void setStartAngle(double newStartAngle);

    double endAngle() const;
    void setEndAngle(double newEndAngle);

    int score() const;



    bool selected() const;
    void setSelected(bool newSelected);

    const QString &caption() const;
    void setCaption(const QString &newCaption);

    void setScore(int newScore);

    const QColor &backColor() const;
    void setBackColor(const QColor &newBackColor);

signals:
private:
    double m_startAngle;
    double m_endAngle;
    int m_score;
    QString m_caption;
    bool m_selected;
    QColor m_backColor;


};

#endif // BALANCEWHEELITEM_H
