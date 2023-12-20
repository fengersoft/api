#include "htmleditor.h"
#include "qwebenginepage.h"
#include "qwebengineview.h"
#include "ui_htmleditor.h"

HtmlEditor::HtmlEditor(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::HtmlEditor)
{
    ui->setupUi(this);
    m_view = new QWebEngineView(this);
    m_view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    m_view->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    m_view->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    m_view->settings()->setAttribute(QWebEngineSettings::LocalStorageEnabled, true);
    m_view->settings()->setAttribute(QWebEngineSettings::XSSAuditingEnabled, true);
    m_view->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);

    connect(m_view, &QWebEngineView::loadProgress, this, &HtmlEditor::onLoadProgress);
    addWidgetToPage(this, m_view);
    m_contentEditable = false;







}

HtmlEditor::~HtmlEditor()
{


    delete ui;
}

void HtmlEditor::onLoadProgress(int progress)
{
    qDebug() << progress;
    if (progress == 100)
    {
        setContentEditable(m_contentEditable);

    }

}

bool HtmlEditor::contentEditable() const
{
    return m_contentEditable;
}

void HtmlEditor::setContentEditable(bool newContentEditable)
{
    m_contentEditable = newContentEditable;
    if (m_contentEditable)
    {
        m_view->page()->runJavaScript("document.body.contentEditable='true';");
    }
    else
    {
        m_view->page()->runJavaScript("document.body.contentEditable='false';");
    }
}

void HtmlEditor::loadFromFile(QString path)
{
    m_path = path;
    m_view->load(QUrl::fromLocalFile(m_path));

}

void HtmlEditor::loadFromUrl(QString url)
{
    m_path = url;
    m_view->load(QUrl(url));
}

void HtmlEditor::saveToFile(QString path)
{

    m_savePath = path;
    m_view->page()->toHtml([this](const QString & html) mutable
    {

        QFile file(m_savePath);
        file.open(QIODevice::WriteOnly);
        file.write(html.toLocal8Bit());
        file.close();

    });




}


