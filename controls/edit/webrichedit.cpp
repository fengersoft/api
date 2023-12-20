#include "webrichedit.h"
#include "ui_webrichedit.h"

WebRichEdit::WebRichEdit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebRichEdit)
{
    ui->setupUi(this);
    m_viewer=new QWebEngineView(this);
    m_viewer->page()->settings()->setAttribute(QWebEngineSettings::XSSAuditingEnabled,true);
    m_viewer->page()->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
     m_viewer->page()->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);

    addWidgetToPage(this,m_viewer);
     m_viewer->load(QUrl("http://127.0.0.1:8848/demo/like-qq-doc.html"));

}

WebRichEdit::~WebRichEdit()
{
    delete ui;
}
