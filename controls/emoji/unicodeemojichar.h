#ifndef UNICODEEMOJICHAR_H
#define UNICODEEMOJICHAR_H

#include <QObject>
#include <QRect>

class UnicodeEmojiChar : public QObject
{
    Q_OBJECT
public:
    explicit UnicodeEmojiChar(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);

    const QString &info() const;
    void setInfo(const QString &newInfo);

    const QRect &rect() const;
    void setRect(const QRect &newRect);

    bool isSelected() const;
    void setIsSelected(bool newIsSelected);

signals:
private:
    QString m_name;
    QString m_info;
    QRect m_rect;
    bool m_isSelected;

};

#endif // UNICODEEMOJICHAR_H
