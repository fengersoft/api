#include "editappinfodialog.h"
#include "ui_editappinfodialog.h"

EditAppInfoDialog::EditAppInfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAppInfoDialog)
{
    ui->setupUi(this);
}

EditAppInfoDialog::~EditAppInfoDialog()
{
    delete ui;
}

void EditAppInfoDialog::on_btnCancel_clicked()
{
    reject();
}


void EditAppInfoDialog::on_btnOk_clicked()
{
    accept();
}


void EditAppInfoDialog::on_btnOpen_clicked()
{
    QString path=QFileDialog::getOpenFileName();
    if (path=="")
    {
        return;
    }
    ui->edtPath->setText(path);
    QFileInfo info(path);
    ui->edtCaption->setText(info.fileName());

}

const QString &EditAppInfoDialog::path() const
{
    m_path=ui->edtPath->text();
    return m_path;
}

void EditAppInfoDialog::setPath(const QString &newPath)
{
    m_path = newPath;
    ui->edtPath->setText(m_path);
}

const QString &EditAppInfoDialog::caption() const
{
    m_caption=ui->edtCaption->text();
    return m_caption;
}

void EditAppInfoDialog::setCaption(const QString &newCaption)
{
    m_caption = newCaption;
    ui->edtCaption->setText(m_caption);
}

