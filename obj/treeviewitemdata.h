
#ifndef TREEVIEWITEMDATA_H
#define TREEVIEWITEMDATA_H


#include <QObject>
#include <QStandardItem>
#include <QStandardItemModel>
#include <functional>


class TreeviewItemData : public QObject
{
    Q_OBJECT
public:
    explicit TreeviewItemData(QObject* parent = nullptr);

    int pid() const;
    void setPid(int newPid);

    int id() const;
    void setId(int newId);



    QString name() const;
    void setName(const QString& newName);

signals:
private:
    int m_pid;
    int m_id;
    QString m_name;

};
QStandardItem* createItem(TreeviewItemData* data);
void addTreeviewItemDatasToModel(QStandardItemModel* model, QStandardItem* parentItem, int pid,
                                 QList<TreeviewItemData*>& datas,
                                 std::function<void(QStandardItem* item)> onAfterAddItem=nullptr);
int getTreeviewItemDataPid(QStandardItem* item);
int getTreeviewItemDataId(QStandardItem* item);
#endif // TREEVIEWITEMDATA_HI
