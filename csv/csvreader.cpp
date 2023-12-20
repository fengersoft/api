#include "csvreader.h"

CsvReader::CsvReader(QObject* parent) : QObject(parent)
{
    m_breakMark = "\r\n";

}

CsvReader::~CsvReader()
{
    clearRowDatas();
}

QString CsvReader::fileName() const
{
    return m_fileName;
}

void CsvReader::setFileName(const QString& fileName)
{
    m_fileName = fileName;
}

void CsvReader::loadfromFileName(QString& fileName)
{
    clearRowDatas();
    m_fileName = fileName;
    QFile file(m_fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QString infos = readString(data);

    QStringList rows = infos.split(m_breakMark);
    int n = 0;
    for (const QString& info : rows)
    {
        n++;
        QString s = "";
        bool bs = false;
        QStringList cols;
        int i = 0;
        while (i < info.length())
        {
            if (bs == false)
            {
                if (info.at(i) == ',')
                {
                    cols << s;
                    s = "";
                }
                else if (info.at(i) == '\"')
                {
                    bs = true;
                }
                else
                {
                    s = s.append(info.at(i));
                }
                i++;
            }
            else
            {
                if (info.at(i) == '\"')
                {
                    cols << s;
                    s = "";
                    bs = false;
                    i += 2;
                }
                else
                {
                    s = s.append(info.at(i));
                    i++;
                }
            }
        }
        cols << s;

        rowDatas << cols;
        QApplication::processEvents();

    }





    file.close();
    qDebug() << "read end";
}

void CsvReader::clearRowDatas()
{

    rowDatas.clear();
}

const QString& CsvReader::breakMark() const
{
    return m_breakMark;
}

void CsvReader::setBreakMark(const QString& newBreakMark)
{
    m_breakMark = newBreakMark;
}
