#include "imagecompareviewerwindow.h"
#include "ui_imagecompareviewerwindow.h"

ImageCompareViewerWindow::ImageCompareViewerWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::ImageCompareViewerWindow)
{
    ui->setupUi(this);
    m_imageCompareViewer = new ImageCompareViewer(this);
    setCentralWidget(m_imageCompareViewer);
}

ImageCompareViewerWindow::~ImageCompareViewerWindow()
{
    delete ui;
}

ImageCompareViewer* ImageCompareViewerWindow::imageCompareViewer() const
{
    return m_imageCompareViewer;
}

void ImageCompareViewerWindow::setImageCompareViewer(ImageCompareViewer* newImageCompareViewer)
{
    m_imageCompareViewer = newImageCompareViewer;
}
