#include "fnplaintextedit.h"

FnPlainTextEdit::FnPlainTextEdit(QWidget *parent)
    : QPlainTextEdit{parent}
{

}

int FnPlainTextEdit::blockHeight(QTextBlock block)
{
    return qRound(blockBoundingRect(block).height());


}

QTextBlock FnPlainTextEdit::getFirstVisibleBlock()
{
    return firstVisibleBlock();

}

int FnPlainTextEdit::blockTop(QTextBlock block)
{
    return qRound(blockBoundingGeometry(block).translated(contentOffset()).top());

}

int FnPlainTextEdit::lineNumberWidth()
{
    int n=blockCount();
    int m=0;
    while (n>10)
    {
        m++;
        n/=10;
    }
    return m;

}
