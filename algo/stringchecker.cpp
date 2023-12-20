#include "stringchecker.h"
#include "qglobal.h"

StringChecker::StringChecker(QObject* parent)
    : QObject{parent}
{

}

const QString& StringChecker::info() const
{
    return m_info;
}

void StringChecker::setInfo(const QString& newInfo)
{
    m_info = newInfo;
}

const QSet<QString>& StringChecker::keywords() const
{
    return m_keywords;
}

void StringChecker::setKeywords(const QSet<QString>& newKeywords)
{
    m_keywords = newKeywords;
}

bool StringChecker::isChecked()
{
    bool ret = true;
    for (QString s : qAsConst(m_keywords))
    {
        if (m_info.indexOf(s) < 0)
        {
            ret = false;
            break;
        }

    }

    return ret;


}

bool StringChecker::isChecked(QString info, QSet<QString> keywords)
{
    StringChecker* checker = new StringChecker(nullptr);
    checker->setInfo(info);
    checker->setKeywords(keywords);
    bool ret = checker->isChecked();
    delete checker;
    return ret;

}
