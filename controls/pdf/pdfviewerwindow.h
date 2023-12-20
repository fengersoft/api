#ifndef PDFVIEWERWINDOW_H
#define PDFVIEWERWINDOW_H

#include <QMainWindow>
#include "pdfviewer.h"

namespace Ui
{
class PdfViewerWindow;
}

class PdfViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PdfViewerWindow(QWidget* parent = nullptr);
    ~PdfViewerWindow();

    PdfViewer* viewer() const;
    void setViewer(PdfViewer* newViewer);

private:
    Ui::PdfViewerWindow* ui;
    PdfViewer* m_viewer;
};

#endif // PDFVIEWERWINDOW_H
