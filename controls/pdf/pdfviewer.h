#ifndef PDFVIEWER_H
#define PDFVIEWER_H

#include <QWidget>
#include "QtPdfium/pdfium/qpdfium.h"
#include <QPainter>
#include <QDebug>
#include <QKeyEvent>
#include "../base/widgethelper.h"

namespace Ui
{
class PdfViewer;
}

class PdfViewer : public QWidget
{
    Q_OBJECT

public:
    explicit PdfViewer(QWidget* parent = nullptr);
    ~PdfViewer();

    const QString& filePath() const;
    void setFilePath(const QString& newFilePath);

    int pageIndex() const;
    void setPageIndex(int newPageIndex);
signals:
    void quit();
protected:
    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    Ui::PdfViewer* ui;
    QString m_filePath;
    QPdfium m_pdf;
    int m_pageIndex;
    QImage m_leftPage;
    QImage m_rightPage;
    QRect m_leftPageRect;
    QRect m_rightPageRect;
    QColor m_backgroundColor;
    WidgetHelper* m_helper;
};

#endif // PDFVIEWER_H
