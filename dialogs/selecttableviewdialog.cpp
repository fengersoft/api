#include "selecttableviewdialog.h"
#include "ui_selecttableviewdialog.h"

SelectTableViewDialog::SelectTableViewDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::SelectTableViewDialog)
{
    ui->setupUi(this);
    m_model = new QStandardItemModel();
    ui->lvData->setModel(m_model);
}

SelectTableViewDialog::~SelectTableViewDialog()
{
    delete ui;
}

QStandardItemModel* SelectTableViewDialog::model() const
{
    return m_model;
}

void SelectTableViewDialog::setModel(QStandardItemModel* newModel)
{
    m_model = newModel;
}

QStandardItem* SelectTableViewDialog::selectItem(int column)
{
    QModelIndex index = ui->lvData->currentIndex();
    if (!index.isValid())
    {
        return nullptr;
    }
    QStandardItem* item = m_model->item(index.row(), column);
    return item;
}

SelectTableViewDialog* createSelectTableViewDialog(QString title, QStringList& labels)
{
    SelectTableViewDialog* dlg = new SelectTableViewDialog();
    dlg->setWindowTitle(title);
    QStandardItemModel* model = dlg->model();
    model->setHorizontalHeaderLabels(labels);

    return dlg;
}

void SelectTableViewDialog::on_btnCancel_clicked()
{
    reject();
}


void SelectTableViewDialog::on_btnOk_clicked()
{
    QModelIndex index = ui->lvData->currentIndex();
    if (!index.isValid())
    {
        return;
    }
    accept();
}


void SelectTableViewDialog::on_lvData_doubleClicked(const QModelIndex& index)
{
    emit ui->btnOk->clicked();
}

