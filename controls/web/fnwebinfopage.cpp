#include "fnwebinfopage.h"
#include "ui_fnwebinfopage.h"

FnWebInfoPage::FnWebInfoPage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnWebInfoPage)
{
    ui->setupUi(this);
    m_page = new FnWebPage(ui->wgtPage);
    addWidgetToPage(ui->wgtPage, m_page);
}

FnWebInfoPage::~FnWebInfoPage()
{
    delete ui;
}

void FnWebInfoPage::setUrl(const QString& newUrl)
{
    AbstractWebPage::setUrl(newUrl);
    ui->edtUrl->setText(newUrl);
    m_page->setUrl(newUrl);

}

void FnWebInfoPage::setTitle(const QString& newTitle)
{
    AbstractWebPage::setTitle(newTitle);
    ui->edtTitle->setText(newTitle);

}

QString FnWebInfoPage::url() const
{
    m_url = ui->edtUrl->text();
    return AbstractWebPage::url();


}

QString FnWebInfoPage::title() const
{
    m_title = ui->edtTitle->text();
    return AbstractWebPage::title();

}

void FnWebInfoPage::on_edtUrl_returnPressed()
{
    m_page->setUrl(ui->edtUrl->text());
}

