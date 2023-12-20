#include "functionlistwidget.h"
#include "functionlist.h"
#include "ui_functionlistwidget.h"

FunctionListWidget::FunctionListWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FunctionListWidget)
{
    ui->setupUi(this);
    m_list = new FunctionList(ui->wgtClient);
    addWidgetToPage(ui->wgtClient, m_list);
}

FunctionListWidget::~FunctionListWidget()
{
    delete ui;
}

FunctionList* FunctionListWidget::list() const
{
    return m_list;
}

void FunctionListWidget::setList(FunctionList* newList)
{
    m_list = newList;
}

void FunctionListWidget::on_edtSearch_textChanged(const QString& arg1)
{
    m_list->search(arg1);
}

