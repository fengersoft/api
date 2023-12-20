#ifndef FNMULTITREEDRAW_H
#define FNMULTITREEDRAW_H

#include <QObject>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QStandardItemModel>
#include "fnmultitreenode.h"
#include "../../draw/drawobject.h"


class FnMultiTreeDraw : public QObject
{
    Q_OBJECT
public:
    explicit FnMultiTreeDraw(QObject *parent = nullptr);
    QList<FnMultiTreeNode*> nodes;
    QString text() const;
    void setText(const QString &newText);

    FnMultiTreeNode *root() const;
    void setRoot(FnMultiTreeNode *newRoot);
    void addChild(FnMultiTreeNode* parentNode,FnMultiTreeNode *node);
    void drawNodes(QImage &img);
    void calWidths();
    void calNodeWidth(FnMultiTreeNode *parentNode);
    void drawNode(QPainter& painter,FnMultiTreeNode *parentNode,int top,int centerX);

    int maxLevel2Height() const;
    void setMaxLevel2Height(int newMaxLevel2Height);
    void calMaxLevel2Height();
    void addChildFromModel(QStandardItemModel *model);
    void addModelNode(QStandardItem* parentItem,FnMultiTreeNode* parentNode,QStandardItemModel *model);

signals:
private:
    FnMultiTreeNode *m_root;
    int m_maxLevel2Height;
    DrawObject *m_drawObj;


};

#endif // FNMULTITREEDRAW_H
