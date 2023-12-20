#include "datatreeview.h"
#include "qabstractitemview.h"
#include "qalgorithms.h"
#include "qlist.h"
#include "qsqlquery.h"
#include "qstandarditemmodel.h"


DataTreeView::DataTreeView(QWidget* parent)
    : QTreeView{parent}
{
    m_rootId = "-1";
    m_model = new QStandardItemModel(this);
    setModel(m_model);
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    setHeaderHidden(true);

}

QStandardItemModel* DataTreeView::model() const
{
    return m_model;
}

void DataTreeView::select(QString sql)
{
    m_sql = sql;
    QSqlQuery qry(sql, m_database);
    QList<RowData*>rows;
    int colCount = qry.record().count();
    while (qry.next())
    {
        RowData* row = new RowData();
        for (int j = 0; j < colCount; j++)
        {
            QString v = qry.value(j).toString();
            row->values << v ;
            if (j == 0)
            {
                row->setPid(v);
            }
            else if (j == 1)
            {
                row->setId(v);
            }
            else if (j == 2)
            {
                row->setText(v);
            }


        }
        rows << row;
    }
    addItems(m_rootId, nullptr, rows);
    qDeleteAll(rows);
    rows.clear();



}





const QString& DataTreeView::rootId() const
{
    return m_rootId;
}

void DataTreeView::setRootId(const QString& newRootId)
{
    m_rootId = newRootId;
}

const QSqlDatabase& DataTreeView::database() const
{
    return m_database;
}

void DataTreeView::setDatabase(const QSqlDatabase& newDatabase)
{
    m_database = newDatabase;
}

void DataTreeView::addItems(QString pid, QStandardItem* parentItem, QList<RowData*>& rows)
{
    for (int i = 0; i < rows.count(); i++)
    {
        RowData* row = rows.at(i);
        if (row->pid() == pid)
        {
            QStandardItem* item = new QStandardItem();
            item->setText(row->text());
            if (parentItem == nullptr)
            {

                m_model->appendRow(item);
                addItems(row->id(), item, rows);
            }
            else
            {
                parentItem->appendRow(item);
                addItems(row->id(), item, rows);
            }


        }
    }
}


