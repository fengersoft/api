#include "markdownblock.h"

MarkdownBlock::MarkdownBlock(QObject* parent)
    : QObject{parent}
{
    m_bold = false;
    m_italic = false;

}

bool MarkdownBlock::bold() const
{
    return m_bold;
}

void MarkdownBlock::setBold(bool newBold)
{
    m_bold = newBold;
}

const QString& MarkdownBlock::text() const
{
    return m_text;
}

void MarkdownBlock::setText(const QString& newText)
{
    m_text = newText;
}

bool MarkdownBlock::italic() const
{
    return m_italic;
}

void MarkdownBlock::setItalic(bool newItalic)
{
    m_italic = newItalic;
}
