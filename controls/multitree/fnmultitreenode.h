#ifndef FNMULTITREENODE_H
#define FNMULTITREENODE_H

#include <QObject>
#include <QList>
class FnMultiTreeNode : public QObject
{
    Q_OBJECT
public:
    explicit FnMultiTreeNode(QObject *parent = nullptr);

    QString text() const;
    void setText(const QString &newText);
    QList<FnMultiTreeNode*> childs;

    FnMultiTreeNode *parentNode() const;
    void setParentNode(FnMultiTreeNode *newParentNode);

    int level() const;
    void setLevel(int newLevel);

    int nodeWidth() const;
    void setNodeWidth(int newNodeWidth);

    int needWidth() const;
    void setNeedWidth(int newNeedWidth);
    int calNeedWidth();
    void setChildSumWidth(int newChildSumWidth);
    int childSumWidth() const;

    QString sxh() const;
    void setSxh(const QString &newSxh);

    int topX() const;
    void setTopX(int newTopX);

    int topY() const;
    void setTopY(int newTopY);

    int bottomX() const;
    void setBottomX(int newBottomX);

    int bottomY() const;
    void setBottomY(int newBottomY);

signals:
private:
    QString m_text;
    FnMultiTreeNode* m_parentNode;
    int m_level;
    int m_nodeWidth;
    int m_needWidth;
    int m_childSumWidth;
    QString m_sxh;
    int m_topX;
    int m_topY;
    int m_bottomX;
    int m_bottomY;

};

#endif // FNMULTITREENODE_H
