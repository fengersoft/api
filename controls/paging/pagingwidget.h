#ifndef PAGINGWIDGET_H
#define PAGINGWIDGET_H

#include "pageswidget.h"
#include <QWidget>
#include <QRegularExpressionValidator>
#include "../base/fnwidgetapi.h"

namespace Ui
{
class PagingWidget;
}

class PagingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PagingWidget(QWidget* parent = nullptr);
    ~PagingWidget();

    int pageCount() const;
    void setPageCount(int newPageCount);
    int currentPageNum() const;
    void setCurrentPageNum(int newCurrentPageNum);

signals:
    void getPageNum(int pageNum);
private slots:
    void on_btnFirst_clicked();

    void on_btnLast_clicked();

    void on_edtPage_returnPressed();
    void onGetPageNum(int pageNum);
    void on_btnPre_clicked();

    void on_btnNext_clicked();

private:
    Ui::PagingWidget* ui;

    int m_pageCount;
    pagesWidget* m_pagesWidget;
    int m_currentPageNum;
};

#endif // PAGINGWIDGET_H
