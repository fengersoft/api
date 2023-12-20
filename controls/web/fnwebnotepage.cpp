#include "fnwebnotepage.h"
#include "ui_fnwebnotepage.h"

FnWebNotePage::FnWebNotePage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::FnWebNotePage)
{
    ui->setupUi(this);
    m_page = new FnWebPage(ui->wgtPage);
    addWidgetToPage(ui->wgtPage, m_page);
}

FnWebNotePage::~FnWebNotePage()
{
    delete ui;
}

QString FnWebNotePage::url() const
{
    return m_url;
}

void FnWebNotePage::setUrl(const QString &newUrl)
{
    m_url = newUrl;
    m_page->setUrl(m_url);
}

QWebEnginePage *FnWebNotePage::webPage()
{
    return m_page->view()->page();

}

int FnWebNotePage::id() const
{
    return m_id;
}

void FnWebNotePage::setId(int newId)
{
    m_id = newId;
}

QString FnWebNotePage::title() const
{
    m_title=ui->edtTitle->text();
    return m_title;
}

void FnWebNotePage::setTitle(const QString &newTitle)
{
    m_title = newTitle;
    ui->edtTitle->setText(m_title);
}
