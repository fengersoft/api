#ifndef FNWEBINFOPAGE_H
#define FNWEBINFOPAGE_H

#include <QWidget>
#include "abstractwebpage.h"

namespace Ui
{
class FnWebInfoPage;
}

class FnWebInfoPage : public QWidget, public AbstractWebPage
{
    Q_OBJECT

public:
    explicit FnWebInfoPage(QWidget* parent = nullptr);
    ~FnWebInfoPage();
    void setUrl(const QString& newUrl);
    void setTitle(const QString& newTitle);
    QString url() const;
    QString title() const;
private slots:
    void on_edtUrl_returnPressed();

private:
    Ui::FnWebInfoPage* ui;
};

#endif // FNWEBINFOPAGE_H
