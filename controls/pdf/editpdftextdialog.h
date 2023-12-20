#ifndef EDITPDFTEXTDIALOG_H
#define EDITPDFTEXTDIALOG_H

#include <QDialog>
#include <QImage>
#include "../api/ocr/ocrapi.h"

namespace Ui
{
class EditPdfTextDialog;
}

class EditPdfTextDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditPdfTextDialog(QWidget* parent = nullptr);
    ~EditPdfTextDialog();

    QImage image() const;
    void setImage(const QImage& newImage);

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

private:
    Ui::EditPdfTextDialog* ui;
    QImage m_image;
};

#endif // EDITPDFTEXTDIALOG_H
