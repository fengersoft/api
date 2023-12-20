#ifndef SINGLEPDFPAGE_H
#define SINGLEPDFPAGE_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QWheelEvent>
#include <QtPdfium/pdfium/qpdfium.h>
#include <QFileDialog>

namespace Ui
{
class SinglePdfPage;
}

class SinglePdfPage : public QWidget
{
    Q_OBJECT

public:
    explicit SinglePdfPage(QWidget* parent = nullptr);
    ~SinglePdfPage();
    void loadFromFile(QString filePath);

    int pageIndex() const;
    void setPageIndex(int newPageIndex);
    QColor backgroundColor() const;
    void setBackgroundColor(const QColor& newBackgroundColor);

    int pageCount() const;
    void setPageCount(int newPageCount);
    void nextPage();
    void prePage();
    void firstPage();
    void lastPage();
    void saveCurrentPageAsImage();
    QImage currentPageAsImage();
    bool isValidPageIndex(int pageIndex);
    QString filePathName() const;
    void setFilePathName(const QString& newFilePathName);

signals:
    void currentPageIndex(int pageIndex);
protected:
    void paintEvent(QPaintEvent* event);
    void wheelEvent(QWheelEvent* event);

private:
    Ui::SinglePdfPage* ui;
    QPdfium m_pdf;
    int m_pageIndex;
    QImage m_page;
    QRect m_pageRect;
    QColor m_backgroundColor;
    int m_pageCount;
    QString m_filePathName;
};

#endif // SINGLEPDFPAGE_H
