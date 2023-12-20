#include "editpdftextdialog.h"
#include "ui_editpdftextdialog.h"

EditPdfTextDialog::EditPdfTextDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::EditPdfTextDialog)
{
    ui->setupUi(this);
}

EditPdfTextDialog::~EditPdfTextDialog()
{
    delete ui;
}

QImage EditPdfTextDialog::image() const
{
    return m_image;
}

void EditPdfTextDialog::setImage(const QImage& newImage)
{
    m_image = newImage;
    QString info = getOcrText(m_image);
    ui->edtInfo->setPlainText(info);
}

void EditPdfTextDialog::on_btnCancel_clicked()
{
    reject();
}


void EditPdfTextDialog::on_btnOk_clicked()
{
    accept();
}

