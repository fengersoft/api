#include "pagingwidget.h"
#include "qregularexpression.h"
#include "qvalidator.h"
#include "ui_pagingwidget.h"
#include "pageswidget.h"
PagingWidget::PagingWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::PagingWidget)
{
    ui->setupUi(this);
    m_pagesWidget = new pagesWidget(ui->wgtPages);
    addWidgetToPage(ui->wgtPages, m_pagesWidget);
    connect(m_pagesWidget, &pagesWidget::getPageNum, this, &PagingWidget::onGetPageNum);
    QRegularExpressionValidator* v = new QRegularExpressionValidator(this);
    QRegularExpression re;
    re.setPattern(R"(\d{1,})");
    v->setRegularExpression(re);
    ui->edtPage->setValidator(v);


}

PagingWidget::~PagingWidget()
{
    delete ui;
}

int PagingWidget::pageCount() const
{
    return m_pageCount;
}

void PagingWidget::setPageCount(int newPageCount)
{
    m_pageCount = newPageCount;
    m_pagesWidget->setPageCount(m_pageCount);
    ui->lblPageCount->setText(QString("%1").arg(m_pageCount));
    m_currentPageNum = 1;
}

void PagingWidget::on_btnFirst_clicked()
{
    onGetPageNum(1);
}


void PagingWidget::on_btnLast_clicked()
{
    onGetPageNum(m_pageCount);
}


void PagingWidget::on_edtPage_returnPressed()
{
    int page = ui->edtPage->text().toInt();
    if ((page >= 1) && (page <= m_pageCount))
    {
        getPageNum(page);
    }

}

void PagingWidget::onGetPageNum(int pageNum)
{
    m_currentPageNum = pageNum;
    emit getPageNum(pageNum);

}

int PagingWidget::currentPageNum() const
{
    return m_currentPageNum;
}

void PagingWidget::setCurrentPageNum(int newCurrentPageNum)
{
    m_currentPageNum = newCurrentPageNum;
}


void PagingWidget::on_btnPre_clicked()
{
    if ((m_currentPageNum - 1) > 0)
    {
        m_currentPageNum--;
        getPageNum(m_currentPageNum);
    }
}


void PagingWidget::on_btnNext_clicked()
{
    if ((m_currentPageNum + 1) <= m_pageCount)
    {
        m_currentPageNum++;
        getPageNum(m_currentPageNum);
    }
}

