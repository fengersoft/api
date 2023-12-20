#include "fnricheditblock.h"

FnRichEditBlock::FnRichEditBlock(QObject *parent)
    : QObject{parent}
{
    m_isSelected=false;
    m_pixmap=QPixmap();

}

int FnRichEditBlock::x() const
{
    return m_x;
}

void FnRichEditBlock::setX(int newX)
{
    m_x = newX;
}

int FnRichEditBlock::y() const
{
    return m_y;
}

void FnRichEditBlock::setY(int newY)
{
    m_y = newY;
}

int FnRichEditBlock::width() const
{
    return m_width;
}

void FnRichEditBlock::setWidth(int newWidth)
{
    m_width = newWidth;
}

int FnRichEditBlock::height() const
{
    return m_height;
}

void FnRichEditBlock::setHeight(int newHeight)
{
    m_height = newHeight;
}

const QString &FnRichEditBlock::text() const
{
    return m_text;
}

void FnRichEditBlock::setText(const QString &newText)
{
    m_text = newText;
}

FnRichEditBlockType FnRichEditBlock::blockType() const
{
    return m_blockType;
}

void FnRichEditBlock::setBlockType(FnRichEditBlockType newBlockType)
{
    m_blockType = newBlockType;
}

const QRect &FnRichEditBlock::rect() const
{
    return m_rect;
}

void FnRichEditBlock::setRect(const QRect &newRect)
{
    m_rect = newRect;
}

bool FnRichEditBlock::isSelected() const
{
    return m_isSelected;
}

void FnRichEditBlock::setIsSelected(bool newIsSelected)
{
    m_isSelected = newIsSelected;
}

bool FnRichEditBlock::isLetter() const
{
    return m_isLetter;
}

void FnRichEditBlock::setIsLetter(bool newIsLetter)
{
    m_isLetter = newIsLetter;
}

const QPixmap &FnRichEditBlock::pixmap() const
{
    return m_pixmap;
}

void FnRichEditBlock::setPixmap(const QPixmap &newPixmap)
{
    m_pixmap = newPixmap;
}

const QString &FnRichEditBlock::path() const
{
    return m_path;
}

void FnRichEditBlock::setPath(const QString &newPath)
{
    m_path = newPath;
    m_pixmap=QPixmap(m_path);
    //m_pixmap=m_pixmap.scaledToHeight(128);

}
