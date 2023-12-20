#ifndef IMAGECOMPAREVIEWERWINDOW_H
#define IMAGECOMPAREVIEWERWINDOW_H

#include <QMainWindow>
#include "../controls/imgviewer/imagecompareviewer.h"
#include "../controls/base/fnwidgetapi.h"
namespace Ui
{
class ImageCompareViewerWindow;
}

class ImageCompareViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageCompareViewerWindow(QWidget* parent = nullptr);
    ~ImageCompareViewerWindow();

    ImageCompareViewer *imageCompareViewer() const;
    void setImageCompareViewer(ImageCompareViewer *newImageCompareViewer);

private:
    Ui::ImageCompareViewerWindow* ui;
    ImageCompareViewer* m_imageCompareViewer;
};

#endif // IMAGECOMPAREVIEWERWINDOW_H
