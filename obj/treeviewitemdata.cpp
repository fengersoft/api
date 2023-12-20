
#include "treeviewitemdata.h"

TreeviewItemData::TreeviewItemData(QObject* parent)
    : QObject{parent}
{

}

int TreeviewItemData::pid() const
{
    return m_pid;
}

void TreeviewItemData::setPid(int newPid)
{
    m_pid = newPid;
}

int TreeviewItemData::id() const
{
    return m_id;
}

void TreeviewItemData::setId(int newId)
{
    m_id = newId;
}

QString TreeviewItemData::name() const
{
    return m_name;
}

void TreeviewItemData::setName(const QString& newName)
{
    m_name = newName;
}



QStandardItem* createItem(TreeviewItemData* data)
{
    QStandardItem* item = new QStandardItem();
    item->setText(data->name());
    item->setData(data->pid(), Qt::UserRole + 1);
    item->setData(data->id(), Qt::UserRole + 2);
    return item;

}

void addTreeviewItemDatasToModel(QStandardItemModel* model, QStandardItem* parentItem,
                                 int pid, QList<TreeviewItemData*>& datas,
                                 std::function<void(QStandardItem*)> onAfterAddItem)
{
    if (parentItem == nullptr)
    {
        model->clear();
    }
    bool hasFind = false;
    for (int i = 0; i < datas.count(); i++)
    {
        TreeviewItemData* data = datas.at(i);
        if (data->pid() == pid)
        {
            hasFind = true;
            QStandardItem* item = createItem(data);
            if (onAfterAddItem!=nullptr)
            {
                onAfterAddItem(item);
            }
            if (parentItem == nullptr)
            {

                model->appendRow(item);



            }
            else
            {
                parentItem->appendRow(item);
            }
            addTreeviewItemDatasToModel(model, item, data->id(), datas,onAfterAddItem);

        }
        else
        {
            if (hasFind)
            {
                break;
            }
        }
    }

}

int getTreeviewItemDataPid(QStandardItem* item)
{
    return item->data(Qt::UserRole + 1).toInt();

}

int getTreeviewItemDataId(QStandardItem* item)
{
    return item->data(Qt::UserRole + 2).toInt();


}
