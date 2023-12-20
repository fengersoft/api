#include "balancewheel.h"
#include "ui_balancewheel.h"

BalanceWheel::BalanceWheel(QWidget* parent) :
    CoachingTool(parent),
    ui(new Ui::BalanceWheel)
{
    ui->setupUi(this);
    double d=-180;
    for (int i = 0; i < 8; i++)
    {
        items[i] = new BalanceWheelItem();
        items[i]->setStartAngle(d);
        items[i]->setEndAngle(d+45);
        d+=45;
    }


}

BalanceWheel::~BalanceWheel()
{
    for (int i = 0; i < 8; i++)
    {
        delete items[i];
    }
    delete ui;
}

double BalanceWheel::getCurAndle()
{
    QPoint curPt = m_helper->cursorPos();
    int y = curPt.y() - m_center.y();
    int x = curPt.x() - m_center.x();
    double r = sqrt(x * x + y * y);

    if (r < m_radius)
    {

        double d = atan2(y, x) * (180 / 3.1415926);
        return d;
    }
    return -360;

}

BalanceWheelItem *BalanceWheel::item(int i)
{
    return items[i];

}

void BalanceWheel::paintEvent(QPaintEvent* event)
{
    QPainter painter;
    painter.begin(this);
    QFont font;
    painter.fillRect(m_helper->clientRect(),QBrush(Qt::white));

    int w = width() < height() ? width() : height();
    w = w - 80;
    m_radius = w / 2;
    QRect clientRc((width() - w) / 2, (height() - w) / 2, w, w);
    m_center = clientRc.center();

    double curAngle=getCurAndle();


    for (int i = 0; i < 8; i++)
    {




        if ((items[i]->endAngle()>=curAngle) && (items[i]->startAngle()<=curAngle))
        {
            items[i]->setSelected(true);
            painter.setBrush(QColor(204, 232, 255));
        }else
        {
            items[i]->setSelected(false);
          painter.setBrush(items[i]->backColor());
        }
        int w2=trunc(w*items[i]->score()/10);
        QRect drawRc(clientRc.center().x()-w2/2,clientRc.center().y()-w2/2,w2,w2);

        painter.setPen(Qt::NoPen);
        painter.drawPie(drawRc,  135 * 16 - i * 45 * 16, 45 * 16);

        if (items[i]->selected())
        {

            painter.setBrush(QColor(204, 232, 255,60));
        }else
        {

          painter.setBrush(Qt::NoBrush);
        }
        painter.setPen(QColor(197,197,197));
        painter.drawPie(clientRc,  135 * 16 - i * 45 * 16, 45 * 16);
         painter.setPen(Qt::black);

        font=painter.font();
        font.setPixelSize(16);
        painter.setFont(font);

        w2=100;
        QRect scoreRc(m_center.x()+w2*cos((i*45+202.5)*(3.141592653/180))-12,
                      m_center.y()+w2*sin((i*45+202.5)*(3.141592653/180))-12,24,24);
        painter.drawText(scoreRc,Qt::AlignCenter,QString("%1").arg(items[i]->score()));



        font=painter.font();
        font.setPixelSize(24);
        painter.setFont(font);

        QRect textRc(m_center.x()+300*cos((i*45+202.5)*(3.141592653/180))-128,
                      m_center.y()+300*sin((i*45+202.5)*(3.141592653/180))-12,256,24);
        painter.drawText(textRc,Qt::AlignCenter,items[i]->caption());
    }

    painter.end();

}

void BalanceWheel::mousePressEvent(QMouseEvent* event)
{
    update();


}

void BalanceWheel::mouseMoveEvent(QMouseEvent *event)
{
    update();

}

void BalanceWheel::mouseDoubleClickEvent(QMouseEvent *event)
{
    for(int i=0;i<8;i++)
    {
        if (items[i]->selected())
        {

            EditBalanceWheelItemDialog *dlg=new EditBalanceWheelItemDialog();
            dlg->setCaption(items[i]->caption());
            dlg->setScore(items[i]->score());
            int ret=dlg->exec();

            if (ret==QDialog::Accepted)
            {
                items[i]->setCaption(dlg->caption());
                items[i]->setScore(dlg->score());
                items[i]->setBackColor(dlg->color());

            }

            delete dlg;

            break;

        }
    }
    update();

}
