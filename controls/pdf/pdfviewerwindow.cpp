#include "pdfviewerwindow.h"
#include "ui_pdfviewerwindow.h"

PdfViewerWindow::PdfViewerWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::PdfViewerWindow)
{
    ui->setupUi(this);
    m_viewer = new PdfViewer(this);
    setCentralWidget(m_viewer);
    m_viewer->setFocus();
    connect(m_viewer, &PdfViewer::quit, this, [this]()
    {
        close();
    });
}

PdfViewerWindow::~PdfViewerWindow()
{
    delete ui;
}

PdfViewer* PdfViewerWindow::viewer() const
{
    return m_viewer;
}

void PdfViewerWindow::setViewer(PdfViewer* newViewer)
{
    m_viewer = newViewer;
}
