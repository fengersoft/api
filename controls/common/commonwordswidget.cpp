#include "commonwordswidget.h"
#include "ui_commonwordswidget.h"

CommonWordsWidget::CommonWordsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonWordsWidget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::Popup);
    setAttribute(Qt::WA_DeleteOnClose);
    addValues();

}

CommonWordsWidget::~CommonWordsWidget()
{
    delete ui;
}

void CommonWordsWidget::addValues()
{

    QStringList weekDays;
    weekDays<<"";
    weekDays<<"星期一";
     weekDays<<"星期二";
      weekDays<<"星期三";
       weekDays<<"星期四";
        weekDays<<"星期五";
         weekDays<<"星期六";
          weekDays<<"星期日";
          QDate preDate;
    QDate curDate=QDate::currentDate();
    QString s;
    s=curDate.toString("yyyy-MM-dd")+" "+QString("%1").arg(weekDays[curDate.dayOfWeek()]);
    ui->lvData->addItem(s);

    preDate=curDate.addDays(-1);
    s=preDate.toString("yyyy-MM-dd")+" "+QString("%1").arg(weekDays[preDate.dayOfWeek()]);
    ui->lvData->addItem(s);

     preDate=curDate.addDays(-6-curDate.dayOfWeek());
    QDate afterDate=preDate.addDays(11);
    s=preDate.toString("yyyy.MM.dd")+"-"+afterDate.toString("yyyy.MM.dd");
     ui->lvData->addItem(s);

}

void CommonWordsWidget::on_lvData_itemClicked(QListWidgetItem *item)
{
    qApp->clipboard()->setText(item->text());
    close();
}

