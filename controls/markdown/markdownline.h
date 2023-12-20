#ifndef MARKDOWNLINE_H
#define MARKDOWNLINE_H

#include "qfont.h"
#include <QObject>
#include <QRect>
#include "markdownblock.h"
#include <QDebug>


class MarkdownLine : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownLine(QObject* parent = nullptr);

    const QRect& rect() const;
    void setRect(const QRect& newRect);


    const QString& text() const;
    void setText(const QString& newText);

    const QString& showText() const;
    void setShowText(const QString& newShowText);

    int fontSize() const;
    void setFontSize(int newFontSize);
    void createBlocks(QString s);

    const QList<MarkdownBlock*>& blocks() const;
    void setBlocks(const QList<MarkdownBlock*>& newBlocks);

signals:
private:
    QRect m_rect;
    QString m_text;
    QString m_showText;
    int m_fontSize;
    QList<MarkdownBlock*> m_blocks;
};

#endif // MARKDOWNLINE_H
