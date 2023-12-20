#include "textmerge.h"
#include "ioutils.h"

TextMerge::TextMerge(QObject* parent)
    : QObject{parent}
{

}

const QStringList& TextMerge::fileNames() const
{
    return m_fileNames;
}

void TextMerge::setFileNames(const QStringList& newFileNames)
{
    m_fileNames = newFileNames;
}

void TextMerge::merge(QString fileName)
{
    QStringList retStl;
    for (int i = 0; i < m_fileNames.count(); i++)
    {

        QStringList stl = readStringList(m_fileNames[i]);
        retStl << stl;
    }
    QFile retFile(fileName);
    retFile.open(QIODevice::WriteOnly);

    retFile.write(retStl.join("\n").toLocal8Bit());
    retFile.close();

    qDebug() << retStl;

}
