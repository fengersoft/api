#include "torrentparser.h"

TorrentParser::TorrentParser(QObject* parent)
    : QObject{parent}
{

}

QString TorrentParser::pathName() const
{
    return m_pathName;
}

void TorrentParser::setPathName(const QString& newPathName)
{
    m_pathName = newPathName;
}

void TorrentParser::loadFromPathName(QString pathName)
{
    QFile file(pathName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();


    QString s;
    s.append(data);
    while (true)
    {
        QChar token = s[0];
        if (token == 'd')
        {
            s = s.mid(1);
        }
        else if (token == 'e')
        {
            s = s.mid(1);
        }
        else if (token == 'l')
        {
            s = s.mid(1);
        }
        else if (token == 'i')
        {
            int n = s.indexOf("e");
            if (n > 0)
            {
                s = s.mid(n + 1);
            }

        }
        else
        {
            int n = s.indexOf(":");
            int len = s.left(n).toInt();

            int retNum;
            QString value = getValue(s, n + 1, len, retNum);



            if (value == "piece length")
            {
                break;
            }
            m_values << value;
            s = s.mid(n + retNum + 1);

        }
        if (s.indexOf(":") < 0)
        {
            break;
        }

    }



    file.close();

}

int TorrentParser::Key(QString s)
{
    QString s1;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        if (s.at(i) == '0')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '1')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '2')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '3')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '4')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '5')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '6')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '7')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '8')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '9')
        {
            s1 =  s.at(i) + s1;
        }
        else if (s.at(i) == '0')
        {
            s1 =  s.at(i) + s1;
        }
        else
        {
            break;
        }

    }
    return s1.toInt();

}

QString TorrentParser::getValue(QString s, int m, int n, int& retNum)
{
    QString s1 = s.mid(m);

    retNum = 0;
    QByteArray data;
    data.append(s1.toUtf8());
    QString ret = data.left(n);
    retNum = ret.length();
    return ret;


}

QString TorrentParser::name()
{

    for (int i = 0; i < (m_values.count() - 1); i++)
    {
        QString s = m_values[i].toLower();
        if (s.indexOf("name") >= 0)
        {
            return m_values[i + 1];
        }

    }


    return "";

}

QStringList TorrentParser::paths()
{
    QStringList stl;

    for (int i = 0; i < (m_values.count() - 1); i++)
    {
        QString s = m_values[i].toLower();
        if (s.indexOf("path") >= 0)
        {
            stl << m_values[i + 1];
        }

    }


    return stl;

}
