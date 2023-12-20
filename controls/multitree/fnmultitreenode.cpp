#include "fnmultitreenode.h"

FnMultiTreeNode::FnMultiTreeNode(QObject *parent)
    : QObject{parent}
{

}

QString FnMultiTreeNode::text() const
{
    return m_text;
}

void FnMultiTreeNode::setText(const QString &newText)
{
    m_text = newText;
}

FnMultiTreeNode *FnMultiTreeNode::parentNode() const
{
    return m_parentNode;
}

void FnMultiTreeNode::setParentNode(FnMultiTreeNode *newParentNode)
{
    m_parentNode = newParentNode;
}

int FnMultiTreeNode::level() const
{
    return m_level;
}

void FnMultiTreeNode::setLevel(int newLevel)
{
    m_level = newLevel;
}

int FnMultiTreeNode::nodeWidth() const
{
    return m_nodeWidth;
}

void FnMultiTreeNode::setNodeWidth(int newNodeWidth)
{
    m_nodeWidth = newNodeWidth;
}

int FnMultiTreeNode::needWidth() const
{
    return m_needWidth;
}

void FnMultiTreeNode::setNeedWidth(int newNeedWidth)
{
    m_needWidth = newNeedWidth;
}

int FnMultiTreeNode::calNeedWidth()
{
    if (childs.count()==0)
    {
        m_needWidth=m_nodeWidth;
        return m_nodeWidth;
    }else
    {
        int w=0;
        for(int i=0;i<childs.count();i++)
        {
            w+=childs.at(i)->nodeWidth();
        }
        setChildSumWidth(w);
        return w;
    }

}

int FnMultiTreeNode::childSumWidth() const
{
    return m_childSumWidth;
}

void FnMultiTreeNode::setChildSumWidth(int newChildSumWidth)
{
    m_childSumWidth = newChildSumWidth;
}

QString FnMultiTreeNode::sxh() const
{
    return m_sxh;
}

void FnMultiTreeNode::setSxh(const QString &newSxh)
{
    m_sxh = newSxh;
}

int FnMultiTreeNode::topX() const
{
    return m_topX;
}

void FnMultiTreeNode::setTopX(int newTopX)
{
    m_topX = newTopX;
}

int FnMultiTreeNode::topY() const
{
    return m_topY;
}

void FnMultiTreeNode::setTopY(int newTopY)
{
    m_topY = newTopY;
}

int FnMultiTreeNode::bottomX() const
{
    return m_bottomX;
}

void FnMultiTreeNode::setBottomX(int newBottomX)
{
    m_bottomX = newBottomX;
}

int FnMultiTreeNode::bottomY() const
{
    return m_bottomY;
}

void FnMultiTreeNode::setBottomY(int newBottomY)
{
    m_bottomY = newBottomY;
}
