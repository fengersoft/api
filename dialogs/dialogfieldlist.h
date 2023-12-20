#ifndef DIALOGFIELDLIST_H
#define DIALOGFIELDLIST_H

#include <QObject>
#include "dialogfield.h"
#include <QMap>
class DialogFieldList : public QObject
{
    Q_OBJECT
public:
    explicit DialogFieldList(QObject* parent = nullptr);
    void bind(QString name, QWidget* w);
    void value(QString name, QVariant value);
    QVariant value(QString name);
signals:
private:
    QMap<QString, DialogField*> m_fields;

};

#endif // DIALOGFIELDLIST_H
