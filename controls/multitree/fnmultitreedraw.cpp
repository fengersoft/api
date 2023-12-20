#include "fnmultitreedraw.h"

FnMultiTreeDraw::FnMultiTreeDraw(QObject *parent)
    : QObject{parent}
{
    m_drawObj=new DrawObject(this);

}

FnMultiTreeNode *FnMultiTreeDraw::root() const
{
    return m_root;
}

void FnMultiTreeDraw::setRoot(FnMultiTreeNode *newRoot)
{
    m_root = newRoot;
}

void FnMultiTreeDraw::addChild(FnMultiTreeNode *parentNode, FnMultiTreeNode *node)
{
    if (parentNode==nullptr)
    {
        m_root=node;
        node->setParentNode(nullptr);
        node->setLevel(0);
    }else
    {
        parentNode->childs<<node;
        node->setParentNode(parentNode);
        node->setLevel(parentNode->level()+1);

    }
    nodes<<node;
    if (node->level()<2)
    {
        if (node->level()==1)
        {
            node->setSxh(QString("%1").arg(parentNode->childs.count()));
        }
        node->setNodeWidth(node->text().length()*12+32);
    }else
    {
        node->setNodeWidth(26);
        node->setSxh(QString("%1.%2").arg(parentNode->sxh()).arg(parentNode->childs.count()));
    }

}

void FnMultiTreeDraw::drawNodes(QImage &img)
{
    calWidths();
    calMaxLevel2Height();
    qDebug()<<m_root->needWidth();
    int imgWidth=m_root->needWidth()+128;
    img=QImage(imgWidth*2,1000,QImage::Format_RGB888);
    img.setDevicePixelRatio(2);

    QPainter painter;
    painter.begin(&img);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
    painter.fillRect(QRect(0,0,img.width(),img.height()),Qt::white);
    drawNode(painter,m_root,64,imgWidth/2-32);
    painter.end();



}

void FnMultiTreeDraw::calWidths()
{
    calNodeWidth(m_root);
}

void FnMultiTreeDraw::calNodeWidth(FnMultiTreeNode *parentNode)
{
    for(int i=0;i<parentNode->childs.count();i++)
    {
        FnMultiTreeNode *node=parentNode->childs.at(i);
        if (node->childs.count()>0)
        {
            calNodeWidth(node);
        }else
        {
            node->setNeedWidth(node->nodeWidth());
            node->setChildSumWidth(node->nodeWidth());
        }


    }
    int w=parentNode->calNeedWidth();
    w=w>parentNode->nodeWidth()?w:parentNode->nodeWidth();
    parentNode->setNeedWidth(w);


}

void FnMultiTreeDraw::drawNode(QPainter &painter,FnMultiTreeNode *parentNode, int top,int centerX)
{
    QRect textRc;
    if (parentNode->level()<2)
    {
        textRc=QRect(centerX-parentNode->nodeWidth()/2-4,top,parentNode->nodeWidth()-8,24);
    }else
    {
        textRc=QRect(centerX-18,top,24,m_maxLevel2Height);
    }

    painter.drawRect(textRc);
    if (parentNode->level()<2)
    {
        painter.drawText(textRc,Qt::AlignCenter,parentNode->sxh()+" "+parentNode->text());
    }else
    {
        QRect titleRc(textRc.left(),textRc.top(),24,24);
        painter.drawText(titleRc,Qt::AlignCenter,parentNode->sxh());
        QRect infoRc(textRc.left(),textRc.top()+24,24,textRc.height()-24);

        m_drawObj->drawVerText(painter,infoRc,parentNode->text(),Qt::AlignTop);
    }
    if (parentNode->level()>0)
    {
        painter.drawLine(textRc.center().x(),textRc.top(),
                         textRc.center().x(),textRc.top()-16);
        parentNode->setTopX(textRc.center().x());
        parentNode->setTopY(textRc.top()-16);
    }
    if (parentNode->level()<2)
    {
        parentNode->setBottomX(textRc.center().x());
        parentNode->setBottomY(textRc.bottom()+2);
    }

    int l,a,b,w;
    a=parentNode->needWidth();
    b=parentNode->childSumWidth();
    if (a>=b)
    {
        l=centerX-b/2;
        w=b;


           }else
    {
        l=centerX-a/2;
        w=a;
    }
           qDebug()<<"l"<<l<<centerX<<a<<b<<w;
    for(int i=0;i<parentNode->childs.count();i++)
    {
        FnMultiTreeNode *node=parentNode->childs.at(i);
        int topHeight=parentNode->level()<2?64:128;
        drawNode(painter,parentNode->childs.at(i),top+topHeight,l+node->needWidth()/2);
        l+=node->needWidth();
    }
    if (parentNode->childs.count()>1)
    {
        painter.drawLine(parentNode->childs.first()->topX(),parentNode->childs.first()->topY(),
                         parentNode->childs.last()->topX(),parentNode->childs.last()->topY());
        int x=parentNode->bottomX();
        int y=parentNode->childs.last()->topY();
        painter.drawLine(x,y,x,parentNode->bottomY());
    }
}

void FnMultiTreeDraw::calMaxLevel2Height()
{
    int n=0;
    for(int i=0;i<nodes.count();i++)
    {
        FnMultiTreeNode *node=nodes.at(i);
        if (node->level()==2)
        {
            if (node->text().length()>n)
            {
                n=node->text().length();
            }
        }
    }
    n=n*16+32;

    m_maxLevel2Height=n;

}

void FnMultiTreeDraw::addChildFromModel(QStandardItemModel *model)
{
    addModelNode(nullptr,nullptr,model);

}

void FnMultiTreeDraw::addModelNode(QStandardItem* parentItem,FnMultiTreeNode* parentNode, QStandardItemModel *model)
{
    if (parentNode==nullptr)
    {
        for(int i=0;i<model->rowCount();i++)
        {
            QStandardItem *item=model->item(i);
            FnMultiTreeNode *node=new FnMultiTreeNode();
            node->setText(item->text());
            addChild(nullptr,node);
            addModelNode(item,node,model);
        }
    }else
    {
        for(int i=0;i<parentItem->rowCount();i++)
        {
            QStandardItem *item=parentItem->child(i);
            FnMultiTreeNode *node=new FnMultiTreeNode();
            node->setText(item->text());
            addChild(parentNode,node);
            addModelNode(item,node,model);
        }
    }

}
int FnMultiTreeDraw::maxLevel2Height() const
{
    return m_maxLevel2Height;
}

void FnMultiTreeDraw::setMaxLevel2Height(int newMaxLevel2Height)
{
    m_maxLevel2Height = newMaxLevel2Height;
}

