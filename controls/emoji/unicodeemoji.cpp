#include "unicodeemoji.h"
#include "ui_unicodeemoji.h"

UnicodeEmoji::UnicodeEmoji(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnicodeEmoji)
{
    ui->setupUi(this);
    m_helper=new WidgetHelper(this);
    m_helper->setControl(this);
    m_helper->setItemsTop(16);
    m_helper->setMaxTop(16);
    setMouseTracking(true);
}

UnicodeEmoji::~UnicodeEmoji()
{
    delete ui;
}

void UnicodeEmoji::paintEvent(QPaintEvent *event)
{
    QPoint curPt=m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);
    painter.fillRect(m_helper->clientRect(),QBrush(Qt::white));
    int l=16;
    int t=m_helper->itemsTop();
    QFont font=painter.font();
    font.setPixelSize(24);
    font.setFamily("微软雅黑");
    painter.setFont(font);
    for(int i=0;i<m_chars.count();i++)
    {
        UnicodeEmojiChar *obj=m_chars.at(i);
        QRect textRc(l,t,48,48);
        if (obj->isSelected())
        {
            painter.fillRect(textRc,QBrush(QColor(153,201,239)));
        }
        else if (textRc.contains(curPt))
        {
            painter.fillRect(textRc,QBrush(QColor(228,228,228)));
        }
        obj->setRect(textRc);
        painter.drawText(textRc,Qt::AlignCenter,obj->name());
        l+=48+6;
        if (width()-l<70)
        {
            l=16;
            t+=48+6;
        }
    }
    painter.end();

}

void UnicodeEmoji::addEmoji(QString name, QString info)
{
    UnicodeEmojiChar *obj=new UnicodeEmojiChar(this);


    obj->setName(name);
    obj->setInfo(info);
    m_chars<<obj;
    update();

}

void UnicodeEmoji::mouseMoveEvent(QMouseEvent *event)
{
    update();

}

void UnicodeEmoji::mousePressEvent(QMouseEvent *event)
{
    QPoint curPt=m_helper->cursorPos();
    for (UnicodeEmojiChar *obj:m_chars)
    {
       bool b=obj->rect().contains(curPt);
       obj->setIsSelected(b);
       if (b)
       {
          emit clickUnicodeEmojiChar(obj);
       }
    }
    update();

}

void UnicodeEmoji::wheelEvent(QWheelEvent *event)
{
    m_helper->moveTop(event->angleDelta().y());

}
