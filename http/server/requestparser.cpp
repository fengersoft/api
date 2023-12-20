
#include "requestparser.h"

RequestParser::RequestParser(QObject* parent)
    : QObject{parent}
{

}

QString RequestParser::requestInfo() const
{
    return m_requestInfo;
}

void RequestParser::setRequestInfo(const QString& newRequestInfo)
{
    m_requestInfo = newRequestInfo;
    m_requestInfoList = m_requestInfo.split("\r\n");
}

QStringList RequestParser::requestInfoList() const
{
    return m_requestInfoList;
}

void RequestParser::setRequestInfoList(const QStringList& newRequestInfoList)
{
    m_requestInfoList = newRequestInfoList;
}

QString RequestParser::requestPath()
{
    if (m_requestInfoList.count() > 0)
    {
        QString s = m_requestInfoList[0];
        QStringList values = s.split(" ");
        return values[1];
    }
    else
    {
        return "";
    }
}

QString RequestParser::method()
{
    if (m_requestInfoList.count() > 0)
    {
        QString s = m_requestInfoList[0];
        QStringList values = s.split(" ");
        return values[0];
    }
    else
    {
        return "";
    }

}

