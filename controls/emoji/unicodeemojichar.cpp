#include "unicodeemojichar.h"

UnicodeEmojiChar::UnicodeEmojiChar(QObject *parent)
    : QObject{parent}
{
    m_isSelected=false;

}

const QString &UnicodeEmojiChar::name() const
{
    return m_name;
}

void UnicodeEmojiChar::setName(const QString &newName)
{
    m_name = newName;
}

const QString &UnicodeEmojiChar::info() const
{
    return m_info;
}

void UnicodeEmojiChar::setInfo(const QString &newInfo)
{
    m_info = newInfo;
}

const QRect &UnicodeEmojiChar::rect() const
{
    return m_rect;
}

void UnicodeEmojiChar::setRect(const QRect &newRect)
{
    m_rect = newRect;
}

bool UnicodeEmojiChar::isSelected() const
{
    return m_isSelected;
}

void UnicodeEmojiChar::setIsSelected(bool newIsSelected)
{
    m_isSelected = newIsSelected;
}
