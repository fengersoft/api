#include "singlepdfpagewindow.h"
#include "ui_singlepdfpagewindow.h"


SinglePdfPageWindow::SinglePdfPageWindow(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::SinglePdfPageWindow)
{
    ui->setupUi(this);
    m_page = new SinglePdfPage(ui->wgtClient);
    connect(m_page, &SinglePdfPage::currentPageIndex, this, &SinglePdfPageWindow::onCurrentPageIndex);
    addWidgetToPage(ui->wgtClient, m_page);

}

SinglePdfPageWindow::~SinglePdfPageWindow()
{
    delete ui;
}

void SinglePdfPageWindow::loadFromFile(QString filePath)
{
    m_page->loadFromFile(filePath);
    ui->lblPage->setText(QString("/%1").arg(m_page->pageCount()));
    qDebug() << m_page->pageCount();

}

void SinglePdfPageWindow::saveCurrentPageAsImage()
{
    m_page->saveCurrentPageAsImage();

}

void SinglePdfPageWindow::on_btnPre_clicked()
{
    m_page->prePage();
}


void SinglePdfPageWindow::on_btnNext_clicked()
{
    m_page->nextPage();
}


void SinglePdfPageWindow::on_btnFirst_clicked()
{
    m_page->firstPage();
}


void SinglePdfPageWindow::on_btnLast_clicked()
{
    m_page->lastPage();
}

void SinglePdfPageWindow::onCurrentPageIndex(int pageIndex)
{
    ui->edtPage->setText(QString("%1").arg(pageIndex + 1));


}


void SinglePdfPageWindow::on_edtPage_returnPressed()
{
    int pageIndex = ui->edtPage->text().toInt() - 1;
    if (!m_page->isValidPageIndex(pageIndex))
    {
        return;
    }
    m_page->setPageIndex(pageIndex);
}


void SinglePdfPageWindow::on_btnGetText_clicked()
{
    EditPdfTextDialog* dlg = new EditPdfTextDialog();
    dlg->setImage(m_page->currentPageAsImage());
    dlg->exec();
    delete dlg;
}


void SinglePdfPageWindow::on_btnGetAllPdfText_clicked()
{
    EditAllPdfTextDialog* dlg = new EditAllPdfTextDialog();
    dlg->setPageNum(m_page->pageCount());
    dlg->setFilePathName(m_page->filePathName());
    int ret = dlg->exec();
    if (ret == QDialog::Accepted)
    {
        QStringList infos = dlg->pdfInfos();
        emit saveDatas(infos);
    }
    delete dlg;
}



