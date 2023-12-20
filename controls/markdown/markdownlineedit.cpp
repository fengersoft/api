#include "markdownlineedit.h"
#include "qfont.h"
#include "qlineedit.h"
#include "qnamespace.h"
#include "qwidget.h"

MarkdownLineEdit::MarkdownLineEdit(QWidget* parent)
    : QLineEdit{parent}
{
    setStyleSheet(R"(
    background-color: rgba(255, 255, 255, 0);
    color:rgba(255,255,255,255);
    border-color:rgba(255,255,255,255);
    border-width:1px;
)");
    m_markdownLine=nullptr;

}



MarkdownLine* MarkdownLineEdit::markdownLine() const
{
    return m_markdownLine;
}

void MarkdownLineEdit::setMarkdownLine(MarkdownLine* newMarkdownLine)
{
    m_markdownLine = newMarkdownLine;
}

void MarkdownLineEdit::showEdit(MarkdownLine* newMarkdownLine)
{
    m_markdownLine = newMarkdownLine;
    setHidden(false);
    setGeometry(m_markdownLine->rect());
    setText(m_markdownLine->text());
    QFont font=this->font();
    font.setPointSize(m_markdownLine->fontSize());
    this->setFont(font);
    setFocus();

}

void MarkdownLineEdit::hideEdit()
{
    m_markdownLine=nullptr;
    hide();

}

void MarkdownLineEdit::keyPressEvent(QKeyEvent* event)
{
    QLineEdit::keyPressEvent(event);
    if (m_markdownLine==nullptr)
    {
        qDebug()<<"m_markdownLine==nullptr";
        return;
    }
    if (event->key()==Qt::Key_Escape)
    {
        hide();
        return;
    }
    if (event->key() == Qt::Key_Return)
    {
        emit addNewLine(m_markdownLine);
    }

}
