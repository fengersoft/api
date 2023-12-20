#ifndef IMAGECOMPAREVIEWERDIALOG_H
#define IMAGECOMPAREVIEWERDIALOG_H

#include <QDialog>
#include "../controls/imgviewer/imagecompareviewer.h"
#include "../controls/base/fnwidgetapi.h"

namespace Ui
{
class ImageCompareViewerDialog;
}

class ImageCompareViewerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageCompareViewerDialog(QWidget* parent = nullptr);
    ~ImageCompareViewerDialog();

    ImageCompareViewer* imageCompareViewer() const;
    void setImageCompareViewer(ImageCompareViewer* newImageCompareViewer);

private slots:
    void on_btnClose_clicked();

private:
    Ui::ImageCompareViewerDialog* ui;
    ImageCompareViewer* m_imageCompareViewer;
};

#endif // IMAGECOMPAREVIEWERDIALOG_H
