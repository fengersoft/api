#ifndef MARKDOWNBLOCK_H
#define MARKDOWNBLOCK_H

#include <QObject>

class MarkdownBlock : public QObject
{
    Q_OBJECT
public:
    explicit MarkdownBlock(QObject* parent = nullptr);

    bool bold() const;
    void setBold(bool newBold);

    const QString& text() const;
    void setText(const QString& newText);

    bool italic() const;
    void setItalic(bool newItalic);

signals:
private:
    bool m_bold;
    bool m_italic;
    QString m_text;

};

#endif // MARKDOWNBLOCK_H
