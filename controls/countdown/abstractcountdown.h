#ifndef ABSTRACTCOUNTDOWN_H
#define ABSTRACTCOUNTDOWN_H

#include "qdatetime.h"
#include "qpixmap.h"

#include "qwindowdefs.h"
#include <QObject>
#include <QWidget>
#include <QDateTime>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>

enum class CountDownType
{
    CtDay,
    CtMinute
};

class AbstractCountDown : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractCountDown(QWidget* parent = nullptr);

    CountDownType countDownType() const;
    void setCountDownType(CountDownType newCountDownType);

    const QDateTime& startDateTime() const;
    void setStartDateTime(const QDateTime& newStartDateTime);

    const QDateTime& endDateTime() const;
    void setEndDateTime(const QDateTime& newEndDateTime);

    const QPixmap& ringBackGround() const;
    void setRingBackGround(const QPixmap& newRingBackGround);

    int percent() const;
    void setPercent(int newPercent);

    QTimer* timer() const;
    void setTimer(QTimer* newTimer);
    QString remainingTimeInfo();

    const QString& title() const;
    void setTitle(const QString& newTitle);

signals:
public slots:
    void onTimeOut();
protected:
    CountDownType m_countDownType;
    QDateTime m_startDateTime;
    QDateTime m_endDateTime;
    QPixmap m_ringBackGround;
    QPixmap m_snapRingBackGround;
    int m_percent;
    QTimer* m_timer;
    QString m_title;
    void resizeEvent(QResizeEvent* event);

};

#endif // ABSTRACTCOUNTDOWN_H
