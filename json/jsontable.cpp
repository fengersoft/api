#include "jsontable.h"

JsonTable::JsonTable(QObject *parent)
    : QObject{parent}
{

}

const QString &JsonTable::fileName() const
{
    return m_fileName;
}

void JsonTable::setFileName(const QString &newFileName)
{
    m_fileName = newFileName;
}

void JsonTable::loadFromFile(QString fileName)
{
    m_fileName=fileName;
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QByteArray jsonData=file.readAll();
    QJsonDocument jdoc=QJsonDocument::fromJson(jsonData);
    clearRows();
    m_rows=jdoc.array();
    file.close();

}

void JsonTable::newTable(QString fileName)
{
     m_fileName=fileName;

}

void JsonTable::save()
{

    QFile file(m_fileName);
    file.open(QFile::WriteOnly);

    QJsonDocument jdoc;
    jdoc.setArray(m_rows);
    QByteArray jsonData=jdoc.toJson();
    file.write(jsonData);
    file.close();


}

void JsonTable::clearRows()
{
    for (int i=m_rows.count();i>=0;i--)
    {
        m_rows.removeAt(i);
    }

}

void JsonTable::appendData(QJsonObject jobj)
{
    jobj["uuid"]=newNoDashUuid();
    jobj["createTime"]=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_rows.append(jobj);

}

void JsonTable::setData(QString uuid, QJsonObject jobj)
{


    for(int i=0;i<m_rows.count();i++)
    {
        QJsonObject jobj=m_rows[i].toObject();
        if (jobj["uuid"].toString()==uuid)
        {
            m_rows.replace(i,jobj);
            return;
        }
    }
    appendData(jobj);

}

int JsonTable::rowCount()
{
    return m_rows.count();

}

QJsonObject JsonTable::rowData(int i)
{
    return m_rows[i].toObject();

}

QJsonObject JsonTable::randomData()
{
    int i=QRandomGenerator64::global()->bounded(0,m_rows.count());
    return m_rows[i].toObject();

}

bool JsonTable::deleteRow(QString uuid)
{
    bool ret=false;
    for (int i=m_rows.count();i>=0;i--)
    {
       QJsonObject jobj=m_rows.at(i).toObject();
       if (jobj["uuid"].toString()==uuid)
       {
            m_rows.removeAt(i);
            ret=true;
            break;
       }
    }
    return ret;

}

QStandardItemModel* JsonTable::rowsToModel(QStringList fieldNames,QJsonArray rows, QStandardItemModel *model)
{
    model->removeRows(0,model->rowCount());
    for(int i=0;i<rows.count();i++)
    {
        QJsonObject jobj=rows[i].toObject();
        QList<QStandardItem*> items;
        for (int j=0;j<fieldNames.count();j++)
        {
            QStandardItem *item=new QStandardItem();
            item->setText(jobj[fieldNames[j]].toString());
            if (j==0)
            {
                item->setData(jobj["uuid"].toString());
            }
            items<<item;
        }
        model->appendRow(items);
    }

    return model;

}

QStandardItemModel *JsonTable::rowsToModel(QStringList fieldNames, QStandardItemModel *model)
{
    return rowsToModel(fieldNames,m_rows,model);
}

QJsonArray JsonTable::select(QString key, QVariant value, SelectType selectType)
{
    QJsonArray selectRows;
    for (int i=0;i<m_rows.count();i++)
    {
        QJsonObject jobj=m_rows[i].toObject();
        if (selectType==SelectType::StEqual)
        {
            if (jobj[key].toVariant()==value)
            {
                selectRows.append(jobj);
            }
        }else if(selectType==SelectType::StLike)
        {
            if (jobj[key].toString().contains(value.toString()))
            {
                selectRows.append(jobj);
            }
        }
        else if(selectType==SelectType::StNotLike)
                {
                    if (!jobj[key].toString().contains(value.toString()))
                    {
                        selectRows.append(jobj);
                    }
                }
    }

    return selectRows;

}
