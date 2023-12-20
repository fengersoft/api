#ifndef JSONTABLE_H
#define JSONTABLE_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include "../global/globaldata.h"
#include "../sql/sqldef.h"
#include <QDateTime>
#include <QRandomGenerator64>
#include <QStandardItemModel>

class JsonTable : public QObject
{
    Q_OBJECT
public:
    explicit JsonTable(QObject *parent = nullptr);

    const QString &fileName() const;
    void setFileName(const QString &newFileName);
    void loadFromFile(QString fileName);
    void newTable(QString fileName);
    void save();
    void clearRows();

    void appendData(QJsonObject jobj);
    void setData(QString uuid,QJsonObject jobj);
    int rowCount();
    QJsonObject rowData(int i);
    QJsonObject randomData();
    bool deleteRow(QString uuid);
    QStandardItemModel* rowsToModel(QStringList fieldNames,QJsonArray rows,QStandardItemModel* model);
    QStandardItemModel* rowsToModel(QStringList fieldNames,QStandardItemModel* model);
    QJsonArray select(QString key,QVariant value,SelectType selectType=SelectType::StLike);
signals:
private:
    QString m_fileName;
    QJsonArray m_rows;

};

#endif // JSONTABLE_H
