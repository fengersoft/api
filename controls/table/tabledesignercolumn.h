#ifndef TABLEDESIGNERCOLUMN_H
#define TABLEDESIGNERCOLUMN_H

#include <QObject>
#include <QRect>

class TableDesignerColumn : public QObject
{
    Q_OBJECT
public:
    explicit TableDesignerColumn(QObject *parent = nullptr);

    const QString &name() const;
    void setName(const QString &newName);

    const QString &field() const;

    const QString &control() const;
    void setControl(const QString &newControl);

    int width() const;
    void setWidth(int newWidth);

    const QString &dataType() const;
    void setDataType(const QString &newDataType);

    const QString &value() const;
    void setValue(const QString &newValue);

    void setField(const QString &newField);

    const QRect &rect() const;
    void setRect(const QRect &newRect);

signals:
private:
    QString m_name;
    QString m_field;
    QString m_control;
    int m_width;
    QString m_dataType;
    QString m_value;
    QRect m_rect;

};

#endif // TABLEDESIGNERCOLUMN_H
