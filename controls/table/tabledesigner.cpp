#include "tabledesigner.h"
#include "ui_tabledesigner.h"

TableDesigner::TableDesigner(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableDesigner)
{
    ui->setupUi(this);
    m_helper=new WidgetHelper(this);
    m_helper->setControl(this);
}

TableDesigner::~TableDesigner()
{
    delete ui;
}

void TableDesigner::addColumn(QString name,QString field,QString control,QString datatype,QString width,
                              QString value)
{
    TableDesignerColumn *column=new TableDesignerColumn(this);
    column->setName(name);
    column->setField(field);
    column->setControl(control);
    qDebug()<<width;
    column->setWidth(width.toInt());
    column->setValue(value);
    column->setDataType(datatype);

    m_columns<<column;

    update();

}

int TableDesigner::columnCount()
{
    return m_columns.count();

}

void TableDesigner::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    QRect clientRc=m_helper->clientRect();
    painter.fillRect(clientRc,QBrush(Qt::white));
    int l=0;
    for (int i=0;i<m_columns.count();i++)
    {
        TableDesignerColumn *column=m_columns.at(i);
        painter.drawLine(l+column->width(),0,l+column->width(),height());

        QRect rect(l,0,column->width(),height());
        column->setRect(rect);
        QRect nameRect(l,0,column->width(),32);
        painter.drawText(nameRect,Qt::AlignCenter,column->name());

        qDebug()<<column->width();
        l+=column->width();
    }
    painter.end();

}

const QList<TableDesignerColumn *> &TableDesigner::columns() const
{
    return m_columns;
}

void TableDesigner::setColumns(const QList<TableDesignerColumn *> &newColumns)
{
    m_columns = newColumns;
}
