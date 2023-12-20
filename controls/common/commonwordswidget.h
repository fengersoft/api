#ifndef COMMONWORDSWIDGET_H
#define COMMONWORDSWIDGET_H

#include <QWidget>
#include <QDateTime>
#include <QDebug>
#include <QClipboard>
#include <QListWidget>

namespace Ui {
class CommonWordsWidget;
}

class CommonWordsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CommonWordsWidget(QWidget *parent = nullptr);
    ~CommonWordsWidget();
    void addValues();

private slots:
    void on_lvData_itemClicked(QListWidgetItem *item);

private:
    Ui::CommonWordsWidget *ui;
};

#endif // COMMONWORDSWIDGET_H
