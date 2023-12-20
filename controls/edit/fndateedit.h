#ifndef FNDATEEDIT_H
#define FNDATEEDIT_H

#include <QWidget>
#include <QDate>
#include <QScreen>
#include <QPainter>
#include <QRegExp>
#include <QRegExpValidator>
#include "../../draw/drawobject.h"
#include "../base/widgethelper.h"
#include "fndateeditdropdown.h"

namespace Ui {
class FnDateEdit;
}

class FnDateEdit : public QWidget
{
    Q_OBJECT

public:
    explicit FnDateEdit(QWidget *parent = nullptr);
    ~FnDateEdit();
    QString text() const;
    void setText(const QString &newText);
    QString longDateFormat();
    bool isValid();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void focusOutEvent(QFocusEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void onGetDate(QDate date);
private:
    Ui::FnDateEdit *ui;
    DrawObject *m_drawObj;
    QRect m_dropDownButtonRect;
    WidgetHelper* m_helper;
    mutable QString m_text;
};

#endif // FNDATEEDIT_H
