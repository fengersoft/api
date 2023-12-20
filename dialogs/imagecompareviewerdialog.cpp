#include "imagecompareviewerdialog.h"
#include "ui_imagecompareviewerdialog.h"

ImageCompareViewerDialog::ImageCompareViewerDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ImageCompareViewerDialog)
{
    ui->setupUi(this);
    m_imageCompareViewer = new ImageCompareViewer(ui->wgtClient);
    addWidgetToPage(ui->wgtClient, m_imageCompareViewer);
}

ImageCompareViewerDialog::~ImageCompareViewerDialog()
{
    delete ui;
}

ImageCompareViewer* ImageCompareViewerDialog::imageCompareViewer() const
{
    return m_imageCompareViewer;
}

void ImageCompareViewerDialog::setImageCompareViewer(ImageCompareViewer* newImageCompareViewer)
{
    m_imageCompareViewer = newImageCompareViewer;
}

void ImageCompareViewerDialog::on_btnClose_clicked()
{
    close();
}

