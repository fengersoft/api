#include "pdfviewer.h"
#include "ui_pdfviewer.h"

PdfViewer::PdfViewer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::PdfViewer)
{
    ui->setupUi(this);
    setMouseTracking(true);
    m_backgroundColor = QColor(30, 30, 30);
    m_helper = new WidgetHelper(this);
    m_helper->setControl(this);


}

PdfViewer::~PdfViewer()
{
    delete ui;
}

const QString& PdfViewer::filePath() const
{
    return m_filePath;
}

void PdfViewer::setFilePath(const QString& newFilePath)
{
    qDebug() << m_filePath;
    m_filePath = newFilePath;
    m_pdf.loadFile(m_filePath);
    setPageIndex(0);

}

int PdfViewer::pageIndex() const
{
    return m_pageIndex;
}

void PdfViewer::setPageIndex(int newPageIndex)
{
    m_pageIndex = newPageIndex;
    if (m_pageIndex < 0)
    {
        m_pageIndex = 0;
    }
    if (m_pageIndex > m_pdf.pageCount())
    {
        m_pageIndex = m_pdf.pageCount() - 1;
    }
    if (m_pageIndex < m_pdf.pageCount())
    {
        m_leftPage = m_pdf.page(m_pageIndex).image(4);

    }
    else
    {
        m_leftPage = QImage();
    }
    if ((m_pageIndex + 1) < m_pdf.pageCount())
    {
        m_rightPage = m_pdf.page(m_pageIndex + 1).image(4);
    }
    else
    {
        m_rightPage = QImage();
    }
    update();
}

void PdfViewer::paintEvent(QPaintEvent* event)
{
    qDebug() << this->devicePixelRatio();
    QPainter painter;

    painter.begin(this);

    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    QRect clientRect(0, 0, width(), height());
    painter.fillRect(clientRect, QBrush(m_backgroundColor));
    QImage leftPix = m_leftPage.scaledToHeight(height() * 2, Qt::SmoothTransformation);
    qDebug() << leftPix.rect() << height();

    m_leftPageRect = QRect(width() / 2 - leftPix.width() / 2, 0, leftPix.width() / 2, leftPix.height() / 2);
    painter.drawImage(m_leftPageRect, leftPix, leftPix.rect());




    QImage rightPix = m_rightPage.scaledToHeight(height() * 2, Qt::SmoothTransformation);
    m_rightPageRect = QRect(width() / 2 + 1, 0, rightPix.width() / 2, rightPix.height() / 2);
    painter.drawImage(m_rightPageRect, rightPix, rightPix.rect());

    painter.end();

}

void PdfViewer::keyPressEvent(QKeyEvent* event)
{

    if ((event->key() == Qt::Key_Space) || (event->key() == Qt::Key_Right))
    {
        setPageIndex(pageIndex() + 2);
    }
    else if (event->key() == Qt::Key_Left)
    {
        setPageIndex(pageIndex() - 2);
    }
    else if (event->key() == Qt::Key_Escape)
    {
        emit quit();
    }

}

void PdfViewer::mousePressEvent(QMouseEvent* event)
{

}

void PdfViewer::mouseReleaseEvent(QMouseEvent* event)
{

}

void PdfViewer::wheelEvent(QWheelEvent* event)
{
    int d = event->angleDelta().y();
    if (d > 0)
    {
        setPageIndex(pageIndex() - 2);
    }
    else
    {
        setPageIndex(pageIndex() + 2);
    }


}
