#ifndef VERTICALSCROLLBAR_H
#define VERTICALSCROLLBAR_H

#include <QObject>
#include <QPainter>
#include <QDebug>
#include <math.h>
#include <QWidget>
#include "../../draw/drawobject.h"
#include "widgethelper.h"


class VerticalScrollBar : public QObject
{
    Q_OBJECT
public:
    explicit VerticalScrollBar(QObject* parent = nullptr);

    int minValue() const;
    void setMinValue(int newMinValue);

    int value() const;
    void setValue(int newValue);

    int maxValue() const;
    void setMaxValue(int newMaxValue);
    void drawScrollBar(QPainter& painter, QRect drawRect);
    void drawScrollBar(QPainter& painter);
    const QRect& buttonRect() const;
    void setButtonRect(const QRect& newButtonRect);

    QWidget* control() const;
    void setControl(QWidget* newControl);
    bool isPointInButtonRect();
    bool isPointInUpButtonRect();
    bool isPointInDownButtonRect();
    void startMouseDown();
    void startMouseUp();

    bool buttonSelected() const;
    void setButtonSelected(bool newButtonSelected);
    void moveButtonPos(int d);
    int maptoControlValue(int v);
    void moveButton(WidgetHelper* helper);
    bool isValueInBoundary();
    bool isValueInMaxBoundary();

signals:
private:
    int m_minValue;
    int m_value;
    int m_maxValue;
    QRect m_buttonRect;
    QRect m_upButtonRect;
    QRect m_downButtonRect;
    QWidget* m_control;
    bool m_buttonSelected;
    DrawObject* m_drawObj;

};

#endif // VERTICALSCROLLBAR_H
