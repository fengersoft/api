#include "markdownline.h"
#include "markdownblock.h"
#include "qalgorithms.h"
#include "qchar.h"

MarkdownLine::MarkdownLine(QObject* parent)
    : QObject{parent}
{
    m_fontSize = 16;

}

const QRect& MarkdownLine::rect() const
{
    return m_rect;
}

void MarkdownLine::setRect(const QRect& newRect)
{
    m_rect = newRect;
}

const QString& MarkdownLine::text() const
{
    return m_text;
}

void MarkdownLine::setText(const QString& newText)
{
    m_text = newText;
    qDeleteAll(m_blocks);
    m_blocks.clear();
    QString tempText = m_text.trimmed();

    if (tempText.startsWith("# "))
    {
        m_showText = tempText.mid(2);
        m_fontSize = 24;

    }
    else if (tempText.startsWith("## "))
    {
        m_showText = tempText.mid(3);
        m_fontSize = 18;

    }
    else if (tempText.startsWith("### "))
    {
        m_showText = tempText.mid(4);
        m_fontSize = 16;

    }
    else if (tempText.startsWith("#### "))
    {
        m_showText = tempText.mid(5);
        m_fontSize = 14;

    }
    else if (tempText.startsWith("##### "))
    {
        m_showText = tempText.mid(6);
        m_fontSize = 12;

    }
    else if (tempText.startsWith("###### "))
    {
        m_showText = tempText.mid(6);
        m_fontSize = 10;

    }
    else
    {
        m_showText = m_text;
        m_fontSize = 14;
    }
    createBlocks(m_showText);
}

const QString& MarkdownLine::showText() const
{
    return m_showText;
}

void MarkdownLine::setShowText(const QString& newShowText)
{
    m_showText = newShowText;
}

int MarkdownLine::fontSize() const
{
    return m_fontSize;
}

void MarkdownLine::setFontSize(int newFontSize)
{
    m_fontSize = newFontSize;
}

void MarkdownLine::createBlocks(QString s)
{
    bool tag = false;
    QString s1 = "";
    QStringList stl;
    bool tagStart = false;
    QString tagName;
    for (int i = 0; i < s.length(); i++)
    {
        QChar c = s.at(i);
        if (i == 0)
        {
            if (c == '*')
            {
                tag = true;

            }
            else
            {
                tag = false;

            }
            s1 = s1.append(c);



        }
        else
        {
            bool tempTag;
            if (c == '*')
            {
                tempTag = true;
            }
            else
            {
                tempTag = false;
            }


            if (tag == tempTag)
            {
                s1.append(c);
                if ((tag == true) && (tagName == s1))
                {
                    stl << s1;
                    s1 = "";
                }


            }
            else
            {
                QString tempTagName = s1;
                if ((tag == true) && (tempTag == false))
                {
                    tagName = s1;
                    qDebug() << tagName;
                    stl << s1;
                    s1 = "";
                    s1 = c;
                    tag = !tag;
                }
                else if ((tag == true) && (tagName == tempTagName))
                {
                    stl << s1;
                    s1 = "";
                    s1 = c;
                    tag = !tag;
                }
                else
                {
                    stl << s1;
                    s1 = "";
                    s1 = c;
                    tag = !tag;
                }


            }


        }

    }
    stl << s1;
    qDebug() << stl;
    tagStart = false;
    MarkdownBlock* block = nullptr;
    for (int i = 0; i < stl.count(); i++)
    {
        if ((stl[i] == "**") && (tagStart == false))
        {
            tagStart = true;
            block = new MarkdownBlock(this);
            block->setBold(true);
        }
        else if ((stl[i] == "**") && (tagStart == true))
        {
            tagStart = false;
            m_blocks << block;
            block = nullptr;
        }
        else if ((stl[i] == "*") && (tagStart == false))
        {
            tagStart = true;
            block = new MarkdownBlock(this);
            block->setItalic(true);
        }
        else if ((stl[i] == "*") && (tagStart == true))
        {
            tagStart = false;
            m_blocks << block;
            block = nullptr;
        }
        else if ((stl[i] == "***") && (tagStart == false))
        {
            tagStart = true;
            block = new MarkdownBlock(this);
            block->setItalic(true);
            block->setBold(true);
        }
        else if ((stl[i] == "***") && (tagStart == true))
        {
            tagStart = false;
            m_blocks << block;
            block = nullptr;
        }
        else if (tagStart == true)
        {
            block->setText(stl[i]);
        }
        else
        {
            block = new MarkdownBlock(this);
            block->setText(stl[i]);
            m_blocks << block;
            block = nullptr;

        }
    }

}

const QList<MarkdownBlock*>& MarkdownLine::blocks() const
{
    return m_blocks;
}

void MarkdownLine::setBlocks(const QList<MarkdownBlock*>& newBlocks)
{
    m_blocks = newBlocks;
}
