#ifndef UNICODEEMOJI_H
#define UNICODEEMOJI_H

#include <QWidget>
#include <QPainter>
#include <QWheelEvent>
#include <QTextCodec>
#include "unicodeemojichar.h"
#include "../base/widgethelper.h"

namespace Ui {
class UnicodeEmoji;
}

class UnicodeEmoji : public QWidget
{
    Q_OBJECT

public:
    explicit UnicodeEmoji(QWidget *parent = nullptr);
    ~UnicodeEmoji();

    void addEmoji(QString name,QString info);
signals:
    void clickUnicodeEmojiChar(UnicodeEmojiChar* obj);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    Ui::UnicodeEmoji *ui;
    QList<UnicodeEmojiChar*> m_chars;
    WidgetHelper* m_helper;
};

#endif // UNICODEEMOJI_H
