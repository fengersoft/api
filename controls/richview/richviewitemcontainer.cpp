#include "richviewitemcontainer.h"
#include "ui_richviewitemcontainer.h"

RichViewItemContainer::RichViewItemContainer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RichViewItemContainer)
{
    ui->setupUi(this);
    m_clientWidget = nullptr;
}

RichViewItemContainer::~RichViewItemContainer()
{
    delete ui;
}

void RichViewItemContainer::addClietWidget(QWidget* w)
{
    m_clientWidget = w;
    addWidgetToPage(ui->wgtClient, w);


}

QWidget* RichViewItemContainer::clientWidget()
{
    return m_clientWidget;

}

QListWidgetItem *RichViewItemContainer::item() const
{
    return m_item;
}

void RichViewItemContainer::setItem(QListWidgetItem *newItem)
{
    m_item = newItem;
}
