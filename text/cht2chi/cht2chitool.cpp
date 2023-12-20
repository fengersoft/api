
#include "cht2chitool.h"

Cht2ChiTool::Cht2ChiTool(QObject* parent)
    : QObject{parent}
{

}

QString Cht2ChiTool::libraryPath() const
{
    return m_libraryPath;
}

void Cht2ChiTool::setLibraryPath(const QString& newLibraryPath)
{
    m_libraryPath = newLibraryPath;
    QFile file(m_libraryPath);
    file.open(QFile::ReadOnly);
    QByteArray data = file.readAll();
    QJsonDocument jdoc = QJsonDocument::fromJson(data);
    QJsonArray jarr = jdoc.array();
    for (int i = 0; i < jarr.count(); i++)
    {
        QJsonObject jobj = jarr.at(i).toObject();
        m_dict.insert(jobj["cht"].toString(),
                      jobj["chi"].toString());
    }

    file.close();
}

QString Cht2ChiTool::toChi(QString src)
{
    QString dest;
    for (int i = 0; i < src.length(); i++)
    {
        QString ch = src.mid(i, 1);
        dest += m_dict.value(ch, ch);

    }
    return dest;

}

