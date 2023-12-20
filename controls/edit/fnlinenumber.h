#ifndef FNLINENUMBER_H
#define FNLINENUMBER_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QDebug>
#include <QPainter>
#include <QTextBlock>
#include "fnplaintextedit.h"


namespace Ui {
class FnLineNumber;
}

class FnLineNumber : public QWidget
{
    Q_OBJECT

public:
    explicit FnLineNumber(QWidget *parent = nullptr);
    ~FnLineNumber();

    FnPlainTextEdit *textEdit() const;
    void setTextEdit(FnPlainTextEdit *newTextEdit);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::FnLineNumber *ui;
    FnPlainTextEdit *m_textEdit;
};

#endif // FNLINENUMBER_H
