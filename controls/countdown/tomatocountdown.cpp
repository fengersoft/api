#include "tomatocountdown.h"
#include "qbrush.h"
#include "qcolor.h"
#include "qfont.h"
#include "qnamespace.h"
#include "qpainter.h"
#include "qpixmap.h"
#include "qtransform.h"
#include "qwindowdefs.h"
#include "ui_tomatocountdown.h"
#include <cmath>

TomatoCountdown::TomatoCountdown(QWidget* parent) :
    AbstractCountDown(parent),
    ui(new Ui::TomatoCountdown)
{
    ui->setupUi(this);
}

TomatoCountdown::~TomatoCountdown()
{
    delete ui;
}

void TomatoCountdown::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    int diam = width() < height() ? width() : height();
    diam = trunc(diam * 0.8);
    diam = diam - 64;
    diam = diam < 300 ? 300 : diam;
    int penWidth = 20;
    painter.begin(this);
    painter.setRenderHints(QPainter::Antialiasing);

    QRect clientRc((width() - diam) / 2, 32, diam, diam);


    QPen pen = painter.pen();
    pen.setColor(QColor(0, 0, 0, 20));
    pen.setWidth(penWidth + 2);
    painter.setPen(pen);
    painter.drawArc(clientRc, 90 * 16, -360 * 16);

    QBrush brush;

//    QConicalGradient linearGradient(clientRc.center().x(), clientRc.center().y(), 360);    //初始化，设置开始和结束点
//    linearGradient.setColorAt(0, Qt::green);//设置60%-100%的区域为蓝色
//    linearGradient.setColorAt(0.3, Qt::yellow);//设置从0-30%的区域为红色
//    linearGradient.setColorAt(0.5, Qt::red);//设置30%-60%的区域为绿色
//    linearGradient.setColorAt(1.0, Qt::green);//设置60%-100%的区域为蓝色
//    brush = QBrush(linearGradient);

    if (m_snapRingBackGround.isNull())
    {
        m_snapRingBackGround = m_ringBackGround.scaled(width(), height());
    }
    brush.setTexture(m_snapRingBackGround);
    pen.setBrush(brush);

    pen.setWidth(penWidth);
    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    int v = trunc(m_percent * 3.6);
    painter.drawArc(clientRc, 90 * 16, -v * 16);


    QFont font = painter.font();




    painter.setPen(QColor(79, 79, 79));




    int fontHeight = diam / 8;
    font = painter.font();
    font.setPixelSize(fontHeight);
    painter.setFont(font);
    QRect textRc(clientRc.center().x() - diam / 2, clientRc.center().y() - font.pixelSize() / 2, diam, font.pixelSize());
    painter.drawText(textRc, Qt::AlignCenter, QString("%1").arg(m_percent) + "%");

    //painter.drawRect(textRc);

    //获取剩余时间
    int titleFontHeight = trunc(fontHeight / 3);
    font = painter.font();
    font.setPixelSize(titleFontHeight);
    painter.setFont(font);
    painter.setPen(Qt::gray);
    QRect usedRc(clientRc.center().x() - 100, textRc.top() - titleFontHeight - 36, 200,
                 titleFontHeight + 12);
    painter.setPen(QColor(159, 159, 159));
    painter.drawText(usedRc, Qt::AlignCenter, "已过");
    // painter.drawRect(usedRc);

    painter.setPen(QColor(159, 159, 159));

    //获取剩余时间
    QRect remainRc;

    // painter.drawRect(remainRc);

    font = painter.font();
    font.setPixelSize(trunc(fontHeight * 0.4));
    painter.setFont(font);
    remainRc = QRect(clientRc.center().x() - 200, trunc(clientRc.center().y() + diam * 0.25), 400,
                     font.pixelSize() + 18);
    painter.drawText(remainRc, Qt::AlignCenter, remainingTimeInfo());


    font = painter.font();
    font.setPixelSize(titleFontHeight);
    painter.setFont(font);
    remainRc = QRect(clientRc.center().x() - 100, remainRc.top() - font.pixelSize() - 18, 200, titleFontHeight + 12);
    painter.setPen(QColor(179, 179, 179));
    painter.drawText(remainRc, Qt::AlignCenter, "剩余");


    font = painter.font();
    font.setPixelSize(18);
    font.setBold(true);
    painter.setFont(font);
    QRect titleRc(0, clientRc.bottom() + 32, width(), 24);
    painter.setPen(QColor(97, 97, 97));
    painter.drawText(titleRc, Qt::AlignCenter, m_title);



    painter.end();


}
