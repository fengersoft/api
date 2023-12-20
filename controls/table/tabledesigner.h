#ifndef TABLEDESIGNER_H
#define TABLEDESIGNER_H

#include <QWidget>
#include "../base/widgethelper.h"
#include "tabledesignercolumn.h"
#include <QDebug>

namespace Ui {
class TableDesigner;
}

class TableDesigner : public QWidget
{
    Q_OBJECT

public:
    explicit TableDesigner(QWidget *parent = nullptr);
    ~TableDesigner();
    void addColumn(QString name,QString field,QString control,QString datatype,QString width,
                   QString value);
    int columnCount();

    const QList<TableDesignerColumn *> &columns() const;
    void setColumns(const QList<TableDesignerColumn *> &newColumns);

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::TableDesigner *ui;
    WidgetHelper *m_helper;
    QList<TableDesignerColumn*> m_columns;




};

#endif // TABLEDESIGNER_H
