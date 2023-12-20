#include "abstractwebpage.h"

AbstractWebPage::AbstractWebPage()
{

}

QString AbstractWebPage::url() const
{
    return m_url;
}

void AbstractWebPage::setUrl(const QString &newUrl)
{
    m_url = newUrl;
}

int AbstractWebPage::id() const
{
    return m_id;
}

void AbstractWebPage::setId(int newId)
{
    m_id = newId;
}

QString AbstractWebPage::title() const
{
    return m_title;
}

void AbstractWebPage::setTitle(const QString &newTitle)
{
    m_title = newTitle;
}

int AbstractWebPage::dataType() const
{
    return m_dataType;
}

void AbstractWebPage::setDataType(int newDataType)
{
    m_dataType = newDataType;
}
