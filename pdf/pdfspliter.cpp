#include "pdfspliter.h"

PdfSpliter::PdfSpliter(QObject* parent)
    : QObject{parent}
{

}

void PdfSpliter::split()
{
    QPdfium pdf(m_srcPath);
    int pageNum = pdf.pageCount();
    for (int i = 0; i < pageNum; i++)
    {
        QString savePath = m_destFolder + "/" + QString("%1.jpg").arg(i + 1, 4, 10, QLatin1Char('0'));
        if (QFile::exists(savePath))
        {
            continue;
        }
        QImage img = pdf.page(i).image(4.0);
        img.save(savePath, "jpg", 100);
        QApplication::processEvents();
    }

}
