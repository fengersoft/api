#include "setvaluesdialog.h"
#include "ui_setvaluesdialog.h"

SetValuesDialog::SetValuesDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SetValuesDialog)
{
    ui->setupUi(this);
}

SetValuesDialog::~SetValuesDialog()
{
    delete ui;
}

QString SetValuesDialog::caption() const
{
    return m_caption;
}

void SetValuesDialog::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
    ui->lblCaption->setText(m_caption + ":");


}

QStringList SetValuesDialog::values() const
{
    m_values = ui->edtValues->toPlainText().split("\n");
    return m_values;
}

void SetValuesDialog::setValues(const QStringList& newValues)
{
    m_values = newValues;
}

bool setValues(QString title, QString caption, QStringList& values)
{
    bool f = false;
    SetValuesDialog* dlg = new SetValuesDialog(nullptr);
    dlg->setWindowTitle(title);
    dlg->setCaption(caption);
    dlg->setValues(values);
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        values = dlg->values();
        f = true;
    }
    delete dlg;
    return f;

}

void SetValuesDialog::on_btnOk_clicked()
{
    accept();
}


void SetValuesDialog::on_btnCancel_clicked()
{
    reject();
}

