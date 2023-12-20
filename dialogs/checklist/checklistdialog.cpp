#include "checklistdialog.h"
#include "qdatetime.h"
#include "ui_checklistdialog.h"

CheckListDialog::CheckListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckListDialog)
{
    ui->setupUi(this);
    m_model=new QStandardItemModel(this);
    ui->lvData->setModel(m_model);
    QStringList labels;
    labels<<"标题";
    m_model->setHorizontalHeaderLabels(labels);
    QString text=qApp->clipboard()->text();
    qDebug()<<text;
    QStringList stl=text.split("\n");
    for(int i=0;i<stl.count();i++)
    {
        if (stl[i].trimmed()=="")
        {
            continue;
        }
        QStandardItem *item=new QStandardItem();
        item->setText(stl[i]);
        item->setCheckable(true);
        item->setCheckState(Qt::Checked);

        m_model->appendRow(item);
    }
}

CheckListDialog::~CheckListDialog()
{
    delete ui;
}

void CheckListDialog::copyAsText()
{
    QStringList stl;
    QDateTime d=QDateTime::currentDateTime();
    stl<<"";
    stl<<"    "+ui->edtTitle->text();
    stl<<"    "+d.toString("yyyy-MM-dd hh:mm:ss");
    for(int i=0;i<m_model->rowCount();i++)
    {
        QStandardItem *item=m_model->item(i);
        if (item->checkState()==Qt::Checked)
        {
            stl<<"(√) "+item->text();
        }else
        {
            stl<<"( ) "+item->text();
        }
    }
    qDebug()<<stl;
    qApp->clipboard()->setText(stl.join("\n"));


}

void CheckListDialog::copyAsImage()
{
    int h=(m_model->rowCount()+6)*48;

    int w=1080;
    QPixmap pix(w,h);
    QPainter painter(&pix);
    QRect rc(0,0,w,h);
    painter.fillRect(rc,QBrush(Qt::white));
    QFont font=painter.font();
    font.setPixelSize(24);
    painter.setFont(font);
    QStringList stl;
    QDateTime d=QDateTime::currentDateTime();
    stl<<"";
    stl<<"    "+ui->edtTitle->text();
    stl<<"    "+d.toString("yyyy-MM-dd hh:mm:ss");
    for(int i=0;i<m_model->rowCount();i++)
    {
        QStandardItem *item=m_model->item(i);
        if (item->checkState()==Qt::Checked)
        {
            stl<<"✅ "+item->text();
        }else
        {
            stl<<"   "+item->text();
        }
    }
    qDebug()<<stl;

    int t=48;
    for(int i=0;i<stl.count();i++)
    {
        QRect textRc(48,t,width()-64,48);
        painter.drawText(textRc,stl[i],Qt::AlignVCenter|Qt::AlignLeft);
        t+=48;
    }
     painter.end();
     pix.save("d:\\tt.png");
    qApp->clipboard()->setPixmap(pix);

}

void CheckListDialog::on_btnCancel_clicked()
{

    reject();
}


void CheckListDialog::on_btnOk_clicked()
{
    if (ui->rdText->isChecked())
    {
        copyAsText();
    }else if(ui->rdImg->isChecked())
    {
        copyAsImage();
    }
    accept();
}


void showCheckListDialog()
{
    CheckListDialog *dlg=new CheckListDialog();
    dlg->setWindowTitle("检查列表");
    dlg->exec();
    delete dlg;

}
