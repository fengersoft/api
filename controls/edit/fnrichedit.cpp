#include "fnrichedit.h"
#include "ui_fnrichedit.h"

FnRichEdit::FnRichEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FnRichEdit)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_InputMethodEnabled,true);
    setMouseTracking(true);
    m_cursorBlock=nullptr;
    m_helper=new WidgetHelper(this);
    m_helper->setControl(this);
    QStringList menuNames;
    menuNames<<"添加图片";
    for(int i=0;i<menuNames.count();i++)
    {
        QAction *act=new QAction(this);
        act->setText(menuNames[i]);
        connect(act,&QAction::triggered,this,&FnRichEdit::onActionTriggered);
        addAction(act);
    }
}

FnRichEdit::~FnRichEdit()
{
    delete ui;
}

void FnRichEdit::deSelectAll()
{
    for(int i=0;i<m_blocks.count();i++)
    {
        FnRichEditBlock *block=m_blocks.at(i);
        block->setIsSelected(false);
    }
    update();
}

FnRichEditBlock *FnRichEdit::blockInPoint(QPoint pt)
{
    for(int i=0;i<m_blocks.count();i++)
    {
        FnRichEditBlock *block=m_blocks.at(i);
        if (block->rect().contains(pt))
        {
            return block;
        }
    }
    return nullptr;
}

void FnRichEdit::deleteSelected()
{
    for (int i=m_blocks.count()-1;i>=0;i--)
    {
         FnRichEditBlock *block=m_blocks.at(i);
        if (block->isSelected())
         {
             m_blocks.removeAt(i);
            delete block;
         }
    }
    update();

}

void FnRichEdit::onActionTriggered()
{
    QAction *act=static_cast<QAction*>(sender());
    if(act->text()=="添加图片")
    {
        QString path=QFileDialog::getOpenFileName();
        if (path=="")
        {
            return;
        }
        FnRichEditBlock* block=addCommit("m",BtImage,false);
        block->setPath(path);

        update();
    }

}

void FnRichEdit::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mousePressEvent";
    setFocus();
    if (event->button()==Qt::RightButton)
    {
        return;
    }

    deSelectAll();
    m_helper->startMouseDown();
    QPoint curPos=m_helper->cursorPos();
    m_cursorBlock=blockInPoint(curPos);
    if (m_cursorBlock!=nullptr)
    {
        if (curPos.x()<m_cursorBlock->rect().center().x())
        {
            m_insertPos=BpBefore;
        }else
        {
            m_insertPos=BpAfter;
        }
    }


}

void FnRichEdit::inputMethodEvent(QInputMethodEvent *event)
{



    QString s=event->commitString();
    addCommit(s,BtText);


    QWidget::inputMethodEvent(event);


}

void FnRichEdit::keyPressEvent(QKeyEvent *event)
{

    if(event->key()==Qt::Key_Backspace)
    {
        if (selectBlockCount()==0)
        {
            if (m_cursorBlock!=nullptr)
            {
                int n=m_blocks.indexOf(m_cursorBlock);
                m_blocks.removeOne(m_cursorBlock);
                delete m_cursorBlock;
                m_cursorBlock=nullptr;
                n--;
                if ((n>=0) && (n<m_blocks.count()))
                {
                    m_cursorBlock=m_blocks.at(n);
                }

                update();
            }

        }else
        {
            deleteSelected();
        }

        return;
    }

    QString s=event->text();
    addCommit(s,BtText,true);
    update();


}

void FnRichEdit::paintEvent(QPaintEvent *event)
{
    int t=16;
    int l=16;
    QPainter painter;
    painter.begin(this);
    QRect clientRc=m_helper->clientRect();
    painter.fillRect(clientRc,Qt::white);
    QFont font=painter.font();
    font.setPointSize(16);
    painter.setFont(font);
    for(int i=0;i<m_blocks.count();i++)
    {

        FnRichEditBlock *block=m_blocks.at(i);
        QRect blockRc;
        if (block->blockType()==BtText)
        {
            QFontMetrics fm=painter.fontMetrics();
            QRect fmBounding=fm.boundingRect(block->isLetter()?"A":"我");
            if (block->blockType()==BtImage)
            {
                l=16;
                t+=fmBounding.height()+8;

            }else
            {
                if ((l+fmBounding.width()+17)>width())
                {
                    l=16;
                    t+=fmBounding.height()+8;
                }
            }




             blockRc=QRect(l,t,fmBounding.width(),fmBounding.height());
            block->setRect(blockRc);
            if (block->isSelected())
            {
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(0,120,215));
                QRect backBlock(l,t,fmBounding.width()+2,fmBounding.height());
                painter.drawRect(backBlock);
                painter.setPen(Qt::white);
            }else
            {
                painter.setPen(Qt::black);
                painter.setBrush(Qt::NoBrush);
            }
            painter.drawText(blockRc,Qt::AlignCenter,block->text());

            if (block==m_cursorBlock)
            {
                if ((block->text()=="\r") && (block==m_blocks.last()))
                {
                    int ptX=16;
                    QPoint pt1(ptX,blockRc.bottom()+8);
                    QPoint pt2(ptX,blockRc.bottom()+blockRc.height()+8);
                    painter.drawLine(pt1,pt2);
                }else
                {
                    int ptX=m_insertPos==BpBefore?(blockRc.left()-1):
                                  (blockRc.right()+1);
                    QPoint pt1(ptX,blockRc.top());
                    QPoint pt2(ptX,blockRc.bottom());
                    painter.drawLine(pt1,pt2);

                }


            }
            l=l+fmBounding.width()+2;
            if (block->text()=="\r")
            {
                l=16;
                t+=fmBounding.height()+8;

            }



        }else
        {
            l=16;
            t+=32;



            QRect pixRc(l,t,block->pixmap().width(),block->pixmap().height());
            painter.drawPixmap(pixRc,block->pixmap(),block->pixmap().rect());
            block->setRect(pixRc);
            t+=block->pixmap().height()+8;


        }






    }
    painter.end();


}

void FnRichEdit::mouseMoveEvent(QMouseEvent *event)
{
    if (m_helper->mousedownFlag())
    {
        deSelectAll();
        QPoint endPt=m_helper->cursorPos();
        FnRichEditBlock *startBlock=blockInPoint(m_helper->mousedownPoint());
        if (startBlock==nullptr)
        {
            return;
        }
        FnRichEditBlock *endBlock=blockInPoint(endPt);
        if (endBlock==nullptr)
        {
            return;
        }
        int m=m_blocks.indexOf(startBlock);
        int n=m_blocks.indexOf(endBlock);
        for (int i=m;i<=n;i++)
        {
            FnRichEditBlock *block=m_blocks.at(i);
            block->setIsSelected(true);
        }

    }



    update();

}

void FnRichEdit::mouseReleaseEvent(QMouseEvent *event)
{
    m_helper->startMouseUp();

}

int FnRichEdit::selectBlockCount()
{
    int n=0;
    for (int i=0;i<m_blocks.count();i++)
    {
        FnRichEditBlock *block=m_blocks.at(i);
        if (block->isSelected())
        {
            n++;
        }
    }
    return n;

}

FnRichEditBlock* FnRichEdit::addCommit(QString s,FnRichEditBlockType blockType,bool isLetter)
{
    if (s=="")
    {
        return nullptr;
    }
    FnRichEditBlock *lastBlock=nullptr;
    QList<FnRichEditBlock*> tempList;
    for(int i=0;i<s.length();i++)
    {
        FnRichEditBlock *block=new FnRichEditBlock(this);
        block->setText(s.at(i));
        block->setBlockType(blockType);
        block->setIsLetter(isLetter);
        tempList<<block;
        lastBlock=block;
    }
    //末尾追加
    qDebug()<<"apend::"<<m_cursorBlock<<s;
    if (m_cursorBlock==nullptr)
    {
        for (int i=0;i<tempList.count();i++)
        {
            m_blocks<<tempList.at(i);

        }

        m_insertPos=BpAfter;
    }else
    {


        int m=m_blocks.indexOf(m_cursorBlock);
        if (m_insertPos==BpAfter)
        {
            m++;
        }
        qDebug()<<m;
        for (int i=0;i<tempList.count();i++)
        {
            m_blocks.insert(m,tempList.at(i));
            m++;

        }

        m_insertPos=BpAfter;


    }
    m_cursorBlock=lastBlock;
    update();
    return m_cursorBlock;

}
