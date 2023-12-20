#ifndef FNWEBNOTEPAGE_H
#define FNWEBNOTEPAGE_H

#include <QWidget>

#include "../base/fnwidgetapi.h"
#include "abstractwebpage.h"

namespace Ui
{
class FnWebNotePage;
}

class FnWebNotePage : public QWidget, public AbstractWebPage
{
    Q_OBJECT

public:
    explicit FnWebNotePage(QWidget* parent = nullptr);
    ~FnWebNotePage();


    QString url() const;
    void setUrl(const QString& newUrl);
    QWebEnginePage* webPage();
    int id() const;
    void setId(int newId);

    QString title() const;
    void setTitle(const QString& newTitle);

private:
    Ui::FnWebNotePage* ui;



};

#endif // FNWEBNOTEPAGE_H
