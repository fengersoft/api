
#include "pdfocrtool.h"

PdfOcrTool::PdfOcrTool(QObject* parent)
    : QObject{parent}
{

}

QString PdfOcrTool::filePathName() const
{
    return m_filePathName;
}

void PdfOcrTool::setFilePathName(const QString& newFilePathName)
{
    m_filePathName = newFilePathName;
}

void PdfOcrTool::loadFromFilePathName(QString pathName)
{
    tesseract::TessBaseAPI* api = getOcrTextApi();
    m_filePathName = pathName;
    QPdfium pdf(m_filePathName);
    for (int i = 0; i < pdf.pageCount(); i++)
    {
        QPdfiumPage page = pdf.page(i);
        QString info = page.text();
        if (info == "")
        {
            QImage img = page.image();

            info = getOcrText(api, img);

        }

        emit progress(i, pdf.pageCount() - 1);
        m_pageTextInfos << info;
        QApplication::processEvents();

    }
    delete api;

}

QStringList& PdfOcrTool::pageTextInfos()
{
    return m_pageTextInfos;
}

