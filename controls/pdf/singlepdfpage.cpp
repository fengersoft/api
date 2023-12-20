#include "singlepdfpage.h"
#include "ui_singlepdfpage.h"

SinglePdfPage::SinglePdfPage(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SinglePdfPage)
{
    ui->setupUi(this);
    m_backgroundColor = Qt::lightGray;
}

SinglePdfPage::~SinglePdfPage()
{
    delete ui;
}

void SinglePdfPage::loadFromFile(QString filePath)
{
    m_pdf.loadFile(filePath);
    m_pageCount = m_pdf.pageCount();
    m_filePathName = filePath;
    setPageIndex(0);

}

int SinglePdfPage::pageIndex() const
{
    return m_pageIndex;
}

void SinglePdfPage::setPageIndex(int newPageIndex)
{
    m_pageIndex = newPageIndex;
    m_page = m_pdf.page(m_pageIndex).image(2.0);
    update();
    emit currentPageIndex(m_pageIndex);
}
void SinglePdfPage::paintEvent(QPaintEvent* event)
{
    int n = this->devicePixelRatio();
    QPainter painter;

    painter.begin(this);

    painter.setRenderHints(QPainter::HighQualityAntialiasing);
    QRect clientRect(0, 0, width(), height());
    painter.fillRect(clientRect, QBrush(m_backgroundColor));
    QImage pix = m_page.scaledToHeight(height() * n, Qt::SmoothTransformation);

    qDebug() << width() << pix.width() / n;
    m_pageRect = QRect((width()  - pix.width() / n) / 2, 0, pix.width() / n, pix.height() / n);
    painter.drawImage(m_pageRect, pix, pix.rect());






    painter.end();

}

void SinglePdfPage::wheelEvent(QWheelEvent* event)
{
    if (event->angleDelta().y() < 0)
    {
        nextPage();
    }
    else
    {
        prePage();
    }

}

QString SinglePdfPage::filePathName() const
{
    return m_filePathName;
}

void SinglePdfPage::setFilePathName(const QString& newFilePathName)
{
    m_filePathName = newFilePathName;
}

int SinglePdfPage::pageCount() const
{
    return m_pageCount;
}

void SinglePdfPage::setPageCount(int newPageCount)
{
    m_pageCount = newPageCount;
}

void SinglePdfPage::nextPage()
{
    if ((m_pageIndex + 1) < m_pageCount)
    {
        m_pageIndex++;
        setPageIndex(m_pageIndex);
    }

}

void SinglePdfPage::prePage()
{
    if ((m_pageIndex - 1) >= 0)
    {
        m_pageIndex--;
        setPageIndex(m_pageIndex);
    }

}

void SinglePdfPage::firstPage()
{
    m_pageIndex = 0;
    setPageIndex(m_pageIndex);

}

void SinglePdfPage::lastPage()
{
    m_pageIndex = m_pageCount - 1;
    setPageIndex(m_pageIndex);
}

void SinglePdfPage::saveCurrentPageAsImage()
{
    QString path = QFileDialog::getSaveFileName();
    m_page.save(path, "jpg");

}

QImage SinglePdfPage::currentPageAsImage()
{
    return m_page;

}

bool SinglePdfPage::isValidPageIndex(int pageIndex)
{
    if (pageIndex < 0)
    {
        return false;
    }
    if (pageIndex > m_pageCount)
    {
        return false;
    }
    return true;

}

QColor SinglePdfPage::backgroundColor() const
{
    return m_backgroundColor;
}

void SinglePdfPage::setBackgroundColor(const QColor& newBackgroundColor)
{
    m_backgroundColor = newBackgroundColor;
    update();
}
