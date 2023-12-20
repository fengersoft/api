#ifndef DIALOGFIELD_H
#define DIALOGFIELD_H

#include <QObject>
#include <QWidget>
#include <QVariant>
#include <QLineEdit>

class DialogField : public QObject
{
    Q_OBJECT
public:
    explicit DialogField(QObject* parent = nullptr);



    QWidget* fieldWidget() const;
    void setFieldWidget(QWidget* newFieldWidget);


    QVariant value() ;
    void setValue(const QVariant& newValue);

signals:
private:
    QWidget* m_fieldWidget;
    QVariant m_value;

};

#endif // DIALOGFIELD_H
