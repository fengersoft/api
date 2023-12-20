#ifndef EDITALLPDFTEXTDIALOG_H
#define EDITALLPDFTEXTDIALOG_H

#include <QDialog>
#include <QListWidget>
#include "../pdf/singlepdfpage.h"
#include "../../controls/base/fnwidgetapi.h"
#include "../api/pdfocr/pdfocrtool.h"

namespace Ui
{
class EditAllPdfTextDialog;
}

class EditAllPdfTextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditAllPdfTextDialog(QWidget* parent = nullptr);
    ~EditAllPdfTextDialog();

    int pageNum() const;
    void setPageNum(int newPageNum);

    QString filePathName() const;
    void setFilePathName(const QString& newFilePathName);

    QStringList pdfInfos() const;
    void setPdfInfos(const QStringList& newPdfInfos);

private slots:
    void on_lvData_itemClicked(QListWidgetItem* item);

    void on_btnGetText_clicked();

    void on_btnCancel_clicked(bool checked);

    void on_btnOk_clicked();

private:
    Ui::EditAllPdfTextDialog* ui;
    SinglePdfPage* m_viewer;
    int m_pageNum;
    QString m_filePathName;
    QStringList m_pdfInfos;
    int m_pageIndex;
};

#endif // EDITALLPDFTEXTDIALOG_H
