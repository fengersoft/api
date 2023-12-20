#ifndef WIDGETHELPER_H
#define WIDGETHELPER_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QPainter>

class WidgetHelper : public QObject
{
    Q_OBJECT
public:
    explicit WidgetHelper(QObject* parent = nullptr);

    bool mousedownFlag() const;
    void setMousedownFlag(bool mousedownFlag);

    QPoint mousedownPoint() const;
    void setMousedownPoint(const QPoint& mousedownPoint);
    void startMouseDown();
    void startMouseUp();
    void mouseMove(int& x, int& y);

    QWidget* control() const;
    void setControl(QWidget* control);
    QPoint cursorPos();
    QPoint virtualCurPos(double dx, double dy);

    int itemsTop() const;
    void setItemsTop(int itemsTop);
    void moveTop(int d);
    void moveLeft(int d);
    QRect clientRect();
    QRect needDrawClientRect(int minTop, int maxHeight);
    QPoint centerPos();
    int radius();
    double factor() const;
    void setFactor(double factor);

    QPoint mouseMovePoint() const;
    void setMouseMovePoint(const QPoint& mouseMovePoint);
    void setMouseMovePoint();
    QRect lastRect() const;
    void setLastRect(const QRect& lastRect);
    QRect innerRect(QRect rc);
    int maxLeft() const;
    void setMaxLeft(int maxLeft);

    int itemsLeft() const;
    void setItemsLeft(int itemsLeft);

    int itemsWidth() const;
    void setItemsWidth(int itemsWidth);

    int maxTop() const;
    void setMaxTop(int newMaxTop);

    bool isClicked();

    bool isTwoPoint() const;
    void setIsTwoPoint(bool newIsTwoPoint);

    bool isTouch() const;
    void setIsTouch(bool newIsTouch);
    void startTouch();
    void endTouch();

    QPoint startTouchPoint0() const;
    void setStartTouchPoint0(QPoint newStartTouchPoint0);

    QPoint startTouchPoint1() const;
    void setStartTouchPoint1(QPoint newStartTouchPoint1);

    double zoomFactor() const;
    void setZoomFactor(double newZoomFactor);

    int startLeft() const;
    void setStartLeft(int newStartLeft);

    int startTop() const;
    void setStartTop(int newStartTop);

    QPoint globalMousedownPoint() const;
    void setGlobalMousedownPoint(QPoint newGlobalMousedownPoint);

    QPoint globalMouseMovePoint() const;
    void setGlobalMouseMovePoint(QPoint newGlobalMouseMovePoint);

    QPoint clickdownPoint() const;
    void setClickdownPoint(QPoint newClickdownPoint);


signals:
private:
    bool m_mousedownFlag;
    QPoint m_mousedownPoint;
    QPoint m_globalMousedownPoint;
    QPoint m_mouseMovePoint;
    QPoint m_globalMouseMovePoint;
    QPoint m_clickdownPoint;
    QWidget* m_control;
    int m_itemsTop;
    int m_itemsLeft;
    double m_factor;
    QRect m_lastRect;
    int m_maxLeft;
    int m_maxTop;
    int m_itemsWidth;

    //多点触摸
    bool m_isTouch;
    bool m_isTwoPoint;
    QPoint m_startTouchPoint0;
    QPoint m_startTouchPoint1;

    //缩放参数
    double m_zoomFactor;
    int m_startLeft;
    int m_startTop;


};

#endif // WIDGETHELPER_H
