#include "richviewtextitem.h"
#include "ui_richviewtextitem.h"

RichViewTextItem::RichViewTextItem(QWidget* parent) :
    QTextEdit(parent),
    ui(new Ui::RichViewTextItem)
{
    ui->setupUi(this);
}

RichViewTextItem::~RichViewTextItem()
{
    delete ui;
}
