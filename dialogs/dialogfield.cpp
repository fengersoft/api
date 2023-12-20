#include "dialogfield.h"
#include "qcombobox.h"
#include "qdatetimeedit.h"
#include "qplaintextedit.h"
#include "qtextedit.h"
#include <cstddef>

DialogField::DialogField(QObject* parent)
    : QObject{parent}
{

}

QWidget* DialogField::fieldWidget() const
{
    return m_fieldWidget;
}

void DialogField::setFieldWidget(QWidget* newFieldWidget)
{
    m_fieldWidget = newFieldWidget;
}

QVariant DialogField::value()
{
    QLineEdit* edit = dynamic_cast<QLineEdit*>(m_fieldWidget);
    QPlainTextEdit* plainEdit = dynamic_cast<QPlainTextEdit*>(m_fieldWidget);
    QComboBox* cbbEdit = dynamic_cast<QComboBox*>(m_fieldWidget);
    QDateTimeEdit* timeEdit = dynamic_cast<QDateTimeEdit*>(m_fieldWidget);
    if (edit != nullptr)
    {
        m_value = edit->text();
    }
    else if (plainEdit != nullptr)
    {
        m_value = plainEdit->toPlainText();
    }
    else if (cbbEdit != nullptr)
    {
        m_value = cbbEdit->currentText();
    }
    else if (timeEdit != nullptr)
    {
        m_value = timeEdit->dateTime();
    }


    return m_value;
}

void DialogField::setValue(const QVariant& newValue)
{
    m_value = newValue;
    QLineEdit* edit = dynamic_cast<QLineEdit*>(m_fieldWidget);
    QDateTimeEdit* timeEdit = dynamic_cast<QDateTimeEdit*>(m_fieldWidget);
    QPlainTextEdit* plainTextEdit=dynamic_cast<QPlainTextEdit*>(m_fieldWidget);
    QComboBox* combobox=dynamic_cast<QComboBox*>(m_fieldWidget);
    if (edit != nullptr)
    {
        edit->setText(m_value.toString());
    }
    else if (timeEdit != nullptr)
    {
        timeEdit->setDate(newValue.toDate());
    }else if (plainTextEdit!=nullptr)
    {
        plainTextEdit->setPlainText(newValue.toString());
    }else if (combobox!=nullptr)
    {
        combobox->setCurrentText(newValue.toString());
    }
}


