#include "fnlinenumber.h"
#include "ui_fnlinenumber.h"

FnLineNumber::FnLineNumber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FnLineNumber)
{
    ui->setupUi(this);
    m_textEdit=nullptr;
}

FnLineNumber::~FnLineNumber()
{
    delete ui;
}

FnPlainTextEdit *FnLineNumber::textEdit() const
{
    return m_textEdit;
}

void FnLineNumber::setTextEdit(FnPlainTextEdit *newTextEdit)
{
    m_textEdit = newTextEdit;
}



void FnLineNumber::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    QTextDocument *doc=m_textEdit->document();
    QTextBlock block=m_textEdit->getFirstVisibleBlock();
    int startShowNum=block.blockNumber();
    int t=m_textEdit->blockTop(block);
    int n=startShowNum;
    QFont font=m_textEdit->font();
    QFontMetrics fm(font);

    while (n<doc->blockCount()) {
       int blockHight=m_textEdit->blockHeight(block);
       QRect textRc(0,t,width(),blockHight);
       painter.drawText(textRc,QString("%1").arg(n+1),Qt::AlignTop|Qt::AlignRight);
       t+=blockHight;
       if (t>height())
       {
           break;
       }
       block=block.next();
       n++;
    }
    painter.end();
}
