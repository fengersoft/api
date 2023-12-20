#include "editallpdftextdialog.h"
#include "ui_editallpdftextdialog.h"

EditAllPdfTextDialog::EditAllPdfTextDialog(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::EditAllPdfTextDialog)
{
    ui->setupUi(this);
    m_pageIndex = -1;
    m_viewer = new SinglePdfPage(ui->wgtPdf);
    addWidgetToPage(ui->wgtPdf, m_viewer);

}

EditAllPdfTextDialog::~EditAllPdfTextDialog()
{
    delete ui;
}

int EditAllPdfTextDialog::pageNum() const
{
    return m_pageNum;
}

void EditAllPdfTextDialog::setPageNum(int newPageNum)
{
    m_pageNum = newPageNum;
    for (int i = 1; i <= m_pageNum; i++)
    {
        ui->lvData->addItem(QString("%1").arg(i));
        m_pdfInfos << "";
    }
}

QString EditAllPdfTextDialog::filePathName() const
{
    return m_filePathName;
}

void EditAllPdfTextDialog::setFilePathName(const QString& newFilePathName)
{
    m_filePathName = newFilePathName;
    m_viewer->loadFromFile(m_filePathName);
}

void EditAllPdfTextDialog::on_lvData_itemClicked(QListWidgetItem* item)
{
    QString text = item->text();
    m_viewer->setPageIndex(text.toInt() - 1);
    if (m_pageIndex != -1)
    {
        m_pdfInfos[m_pageIndex] = ui->edtInfo->toPlainText();
    }
    ui->edtInfo->setPlainText(m_pdfInfos[text.toInt() - 1]);
    m_pageIndex = text.toInt() - 1;
}


void EditAllPdfTextDialog::on_btnGetText_clicked()
{
    PdfOcrTool* tool = new PdfOcrTool();
    connect(tool, &PdfOcrTool::progress, this, [this](int i, int n)
    {
        ui->pb->setMinimum(0);
        ui->pb->setMaximum(n);
        ui->pb->setValue(i);
    });
    tool->loadFromFilePathName(m_viewer->filePathName());
    for (int i = 0; i < m_pdfInfos.count(); i++)
    {
        m_pdfInfos[i] = tool->pageTextInfos()[i];
    }
    delete tool;
}


void EditAllPdfTextDialog::on_btnCancel_clicked(bool checked)
{
    reject();
}


void EditAllPdfTextDialog::on_btnOk_clicked()
{
    accept();

}

QStringList EditAllPdfTextDialog::pdfInfos() const
{
    return m_pdfInfos;
}

void EditAllPdfTextDialog::setPdfInfos(const QStringList& newPdfInfos)
{
    m_pdfInfos = newPdfInfos;
}

