#include "fndateedit.h"
#include "ui_fndateedit.h"

FnDateEdit::FnDateEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FnDateEdit)
{
    ui->setupUi(this);
    ui->edtText->setMinimumHeight(24);
    m_drawObj=new DrawObject(this);
    setMouseTracking(true);
    ui->edtText->setMouseTracking(true);
    m_helper=new WidgetHelper(this);
    m_helper->setControl(this);


}

FnDateEdit::~FnDateEdit()
{
    delete ui;
}

void FnDateEdit::paintEvent(QPaintEvent *event)
{
    QPoint curPt=m_helper->cursorPos();
    QPainter painter;
    painter.begin(this);

    m_dropDownButtonRect=QRect(width()-24,0,24,24);
    if (m_dropDownButtonRect.contains(curPt))
    {
        painter.setPen(QColor(0,125,212));
        painter.setBrush(QColor(229,241,250));
        painter.drawRect(m_dropDownButtonRect);


    }else
    {

        painter.setPen(Qt::lightGray);
        painter.setBrush(Qt::white);
        painter.fillRect(m_dropDownButtonRect,QBrush(Qt::white));
        painter.drawLine(width()-24,0,width(),0);
        painter.drawLine(width()-24,height(),width(),height());
        painter.drawLine(width(),0,width(),height());

    }

    m_drawObj->drawTriangleButton(painter,m_dropDownButtonRect,Qt::lightGray,DrawTriDownV2,8);
    painter.end();


}

void FnDateEdit::mouseMoveEvent(QMouseEvent *event)
{

    repaint();

}

void FnDateEdit::focusOutEvent(QFocusEvent *event)
{
    update();

}

void FnDateEdit::leaveEvent(QEvent *event)
{
    update();

}

void FnDateEdit::mousePressEvent(QMouseEvent *event)
{
     QPoint curPt=m_helper->cursorPos();
     QScreen *screen=QApplication::screenAt(curPt);
    if (m_dropDownButtonRect.contains(curPt))
     {
        FnDateEditDropDown *w=new FnDateEditDropDown(nullptr);
        connect(w,&FnDateEditDropDown::getData,this,&FnDateEdit::onGetDate);
        w->show();
        QPoint pt(0,height()+1);
        pt=this->mapToGlobal(pt);
        if ((pt.x()+w->width())>screen->availableGeometry().width())
        {
            pt=QPoint(width()-w->width(),height()+1);
            pt=this->mapToGlobal(pt);
        }

        w->move(pt);
     }

}

void FnDateEdit::onGetDate(QDate date)
{
     ui->edtText->setText(date.toString("yyyy-MM-dd"));

}

QString FnDateEdit::text() const
{
     m_text=ui->edtText->text();
     return m_text;
}

void FnDateEdit::setText(const QString &newText)
{
     m_text = newText;
     if (m_text.indexOf("T")>0)
     {
        m_text=m_text.left(m_text.indexOf("T"));
     }
     ui->edtText->setText(m_text);
}

QString FnDateEdit::longDateFormat()
{

     return ui->edtText->text()+"T00:00:00.000+00:00";

}

bool FnDateEdit::isValid()
{
     m_text=ui->edtText->text();
     QString r="([0-9]{3}[1-9]|[0-9]{2}[1-9][0-9]{1}|[0-9]{1}[1-9][0-9]{2}|[1-9][0-9]{3})-(((0[13578]|1[02])-(0[1-9]|[12][0-9]|3[01]))|((0[469]|11)-(0[1-9]|[12][0-9]|30))|(02-(0[1-9]|[1][0-9]|2[0-8])))";
     QRegExp exp(r);
     qDebug()<<m_text<<exp.indexIn(m_text);
     return exp.indexIn(m_text)!=-1;


}
