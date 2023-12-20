#include "multilineeditdialog.h"
#include "ui_multilineeditdialog.h"

MultilineEditDialog::MultilineEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultilineEditDialog)
{
    ui->setupUi(this);
}

MultilineEditDialog::~MultilineEditDialog()
{
    delete ui;
}
