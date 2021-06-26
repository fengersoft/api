#ifndef WIDGETHELPER_H
#define WIDGETHELPER_H

#include <QObject>
#include <QWidget>
#include <QDebug>

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

signals:
private:
    bool m_mousedownFlag;
    QPoint m_mousedownPoint;
    QWidget* m_control;


};

#endif // WIDGETHELPER_H
