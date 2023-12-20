#include "dialogfieldlist.h"

DialogFieldList::DialogFieldList(QObject* parent)
    : QObject{parent}
{

}

void DialogFieldList::bind(QString name, QWidget* w)
{

    DialogField* field = m_fields.value(name, nullptr);
    if (field == nullptr)
    {
        field = new DialogField(this);
        field->setFieldWidget(w);
        m_fields[name] = field;

    }

}

void DialogFieldList::value(QString name, QVariant value)
{
    m_fields[name]->setValue(value);

}

QVariant DialogFieldList::value(QString name)
{
    DialogField* field = m_fields.value(name, nullptr);
    if (field == nullptr)
    {
        return QVariant();

    }
    else
    {
        return field->value();
    }

}
