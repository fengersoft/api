#ifndef FNRICHEDITBLOCK_H
#define FNRICHEDITBLOCK_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include <QWidget>


enum FnRichEditBlockType
{
    BtText,
    BtImage

};
enum FnRichEditBlockInsertPos{
    BpBefore,
    BpAfter
};

class FnRichEditBlock : public QObject
{
    Q_OBJECT
public:
    explicit FnRichEditBlock(QObject *parent = nullptr);

    int x() const;
    void setX(int newX);

    int y() const;
    void setY(int newY);

    int width() const;
    void setWidth(int newWidth);

    int height() const;
    void setHeight(int newHeight);

    const QString &text() const;
    void setText(const QString &newText);

    FnRichEditBlockType blockType() const;
    void setBlockType(FnRichEditBlockType newBlockType);

    const QRect &rect() const;
    void setRect(const QRect &newRect);

    bool isSelected() const;
    void setIsSelected(bool newIsSelected);

    bool isLetter() const;
    void setIsLetter(bool newIsLetter);

    const QPixmap &pixmap() const;
    void setPixmap(const QPixmap &newPixmap);

    const QString &path() const;
    void setPath(const QString &newPath);

signals:
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    QString m_text;
    QRect m_rect;
    FnRichEditBlockType m_blockType;
    bool m_isSelected;
    bool m_isLetter;
    QPixmap m_pixmap;
    QString m_path;


};

#endif // FNRICHEDITBLOCK_H
