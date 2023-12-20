#include "tabledesignercolumn.h"

TableDesignerColumn::TableDesignerColumn(QObject *parent)
    : QObject{parent}
{

}

const QString &TableDesignerColumn::name() const
{
    return m_name;
}

void TableDesignerColumn::setName(const QString &newName)
{
    m_name = newName;
}

const QString &TableDesignerColumn::field() const
{
    return m_field;
}

const QString &TableDesignerColumn::control() const
{
    return m_control;
}

void TableDesignerColumn::setControl(const QString &newControl)
{
    m_control = newControl;
}

int TableDesignerColumn::width() const
{
    return m_width;
}

void TableDesignerColumn::setWidth(int newWidth)
{
    m_width = newWidth;
}

const QString &TableDesignerColumn::dataType() const
{
    return m_dataType;
}

void TableDesignerColumn::setDataType(const QString &newDataType)
{
    m_dataType = newDataType;
}

const QString &TableDesignerColumn::value() const
{
    return m_value;
}

void TableDesignerColumn::setValue(const QString &newValue)
{
    m_value = newValue;
}

void TableDesignerColumn::setField(const QString &newField)
{
    m_field = newField;
}

const QRect &TableDesignerColumn::rect() const
{
    return m_rect;
}

void TableDesignerColumn::setRect(const QRect &newRect)
{
    m_rect = newRect;
}
