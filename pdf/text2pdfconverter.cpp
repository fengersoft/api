#include "text2pdfconverter.h"

Text2PdfConverter::Text2PdfConverter(QObject* parent)
    : QObject{parent}
{
    m_backColor = QColor(254, 247, 197);

}

const QString& Text2PdfConverter::srcPath() const
{
    return m_srcPath;
}

const QString& Text2PdfConverter::destPath() const
{
    return m_destPath;
}

void Text2PdfConverter::setDestPath(const QString& newDestPath)
{
    m_destPath = newDestPath;
}

const QColor& Text2PdfConverter::backColor() const
{
    return m_backColor;
}

void Text2PdfConverter::startConvert()
{
    QStringList infos = readStringList(m_srcPath);

    QPrinter printer;
    printer.setResolution(1200);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageMargins(QMargins(0, 0, 0, 0));
    printer.setOutputFileName(m_destPath);
    int singleLineWord = 30;


    QPainter painter;

    painter.begin(&printer);
    QFont font = painter.font();
    font.setPointSize(16);
    painter.setFont(font);



    QFontMetrics fm = painter.fontMetrics();
    int fontHeight = std::trunc(fm.height() * 1.5);
    int t = fontHeight * 2;
#if QT_VERSION>QT_VERSION_CHECK(6,0,0)
    int fontWidth = fm.boundingRect("我").width() * singleLineWord;
#else
    int fontWidth = fm.boundingRect("我").width() * singleLineWord;
#endif
    int lineLeft = (printer.pageRect(QPrinter::DevicePixel).width() - fontWidth) / 2;
    qDebug() << printer.pageRect(QPrinter::Point);

    painter.fillRect(printer.pageRect(QPrinter::DevicePixel),
                     QBrush(m_backColor));

    for (int i = 0; i < infos.count(); i++)
    {
        qDebug() << i << infos[i];
        QApplication::processEvents();
        QStringList stl = stringToStringList(infos[i], singleLineWord);

        for (int j = 0; j < stl.count(); j++)
        {
            painter.drawText(lineLeft, t, stl[j]);
            t += fontHeight;
            if (printer.pageRect(QPrinter::DevicePixel).height() - t < fontHeight * 2)
            {
                t = fontHeight * 2;
                printer.newPage();
                painter.fillRect(printer.pageRect(QPrinter::DevicePixel),
                                 QBrush(m_backColor));
            }

        }
        QApplication::processEvents();


    }
    painter.end();
    qDebug() << "end";


}
QStringList Text2PdfConverter::stringToStringList(QString s, int maxLen)
{
    QString t = s;
    QStringList stl;


    while (t.toLocal8Bit().size() > (maxLen * 2))
    {

        int n = maxLen;
        QString w = t.left(n);
        while ((maxLen * 2 - w.toLocal8Bit().size()) >= 2)
        {

            w += t[n];
            n++;
        }

        stl << w;
        t = t.mid(n);
    }
    stl << t;

    return stl;

}

void Text2PdfConverter::setSrcPath(const QString& newSrcPath)
{
    m_srcPath = newSrcPath;
}
