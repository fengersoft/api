#ifndef FNPINYIN_H
#define FNPINYIN_H

#include <QObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonObject>

class FnPinYin : public QObject
{
    Q_OBJECT
public:
    explicit FnPinYin(QObject *parent = nullptr);
    void loadData();
    QString getJianPin(QString s);
private:
    QMap<QString,QString> m_jianpins;
    QString getFirstLetter(QString s);
signals:

};

#endif // FNPINYIN_H
