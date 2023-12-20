#ifndef SINGLEPDFPAGEWINDOW_H
#define SINGLEPDFPAGEWINDOW_H

#include <QWidget>
#include "singlepdfpage.h"
#include "editpdftextdialog.h"
#include "../base/fnwidgetapi.h"
#include "editallpdftextdialog.h"

namespace Ui
{
class SinglePdfPageWindow;
}

class SinglePdfPageWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SinglePdfPageWindow(QWidget* parent = nullptr);
    ~SinglePdfPageWindow();
    void loadFromFile(QString filePath);
    void saveCurrentPageAsImage();
signals:
    void saveDatas(QStringList& datas);
private slots:
    void on_btnPre_clicked();

    void on_btnNext_clicked();

    void on_btnFirst_clicked();

    void on_btnLast_clicked();
    void onCurrentPageIndex(int pageIndex);

    void on_edtPage_returnPressed();

    void on_btnGetText_clicked();

    void on_btnGetAllPdfText_clicked();


private:
    Ui::SinglePdfPageWindow* ui;
    SinglePdfPage* m_page;
};

#endif // SINGLEPDFPAGEWINDOW_H
