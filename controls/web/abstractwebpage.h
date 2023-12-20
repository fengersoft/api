#ifndef ABSTRACTWEBPAGE_H
#define ABSTRACTWEBPAGE_H
#include <QObject>
#include "fnwebpage.h"

class AbstractWebPage
{
public:
    AbstractWebPage();
    virtual QString url() const;
    virtual void setUrl(const QString& newUrl);

    int id() const;
    virtual void setId(int newId);

    virtual QString title() const;
    virtual  void  setTitle(const QString& newTitle);

    int dataType() const;
    virtual  void setDataType(int newDataType);

protected:
    mutable  QString m_url;
    int m_id;
    mutable QString m_title;
    FnWebPage* m_page;
    int m_dataType;
};

#endif // ABSTRACTWEBPAGE_H
