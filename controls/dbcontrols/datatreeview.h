#ifndef DATATREEVIEW_H
#define DATATREEVIEW_H

#include "qlist.h"
#include "qsqldatabase.h"
#include "qstandarditemmodel.h"
#include <QStandardItemModel>
#include <QObject>
#include <QWidget>
#include <QTreeView>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlField>
#include <QSqlRecord>
#include "../../sql/rowdata.h"

class DataTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit DataTreeView(QWidget* parent = nullptr);

    QStandardItemModel* model() const;
    void select(QString sql);



    const QString& rootId() const;
    void setRootId(const QString& newRootId);

    const QSqlDatabase& database() const;
    void setDatabase(const QSqlDatabase& newDatabase);
    void addItems(QString pid, QStandardItem* parentItem, QList<RowData*>& rows);

signals:

protected:
    QStandardItemModel* m_model;
    QString m_sql;
    QSqlDatabase m_database;
    QString m_rootId;

};

#endif // DATATREEVIEW_H
