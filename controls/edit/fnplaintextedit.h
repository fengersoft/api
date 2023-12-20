#ifndef FNPLAINTEXTEDIT_H
#define FNPLAINTEXTEDIT_H

#include <QObject>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBlock>

class FnPlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit FnPlainTextEdit(QWidget *parent = nullptr);
    int blockHeight(QTextBlock block);
    QTextBlock getFirstVisibleBlock();
    int blockTop(QTextBlock block);
    int lineNumberWidth();
signals:

};

#endif // FNPLAINTEXTEDIT_H
