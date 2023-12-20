#include "editbalancewheelitemdialog.h"
#include "ui_editbalancewheelitemdialog.h"

EditBalanceWheelItemDialog::EditBalanceWheelItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditBalanceWheelItemDialog)
{
    ui->setupUi(this);
    m_toolbar=new ColorToolbar(ui->wgtColor);
    addWidgetToPage(ui->wgtColor,m_toolbar);
    m_toolbar->addDefaultColorButtons();
    m_toolbar->setBackgroundColor(QColor(0,0,0,0));

}

EditBalanceWheelItemDialog::~EditBalanceWheelItemDialog()
{
    delete ui;
}

void EditBalanceWheelItemDialog::on_btnCancel_clicked()
{
    reject();
}


void EditBalanceWheelItemDialog::on_btnOk_clicked()
{
    accept();
}

const QColor &EditBalanceWheelItemDialog::color() const
{
    m_color=m_toolbar->selectColor();
    return m_color;
}

void EditBalanceWheelItemDialog::setColor(const QColor &newColor)
{
    m_color = newColor;
}

const QString &EditBalanceWheelItemDialog::caption() const
{
    m_caption=ui->edtCaption->text();
    return m_caption;
}

void EditBalanceWheelItemDialog::setCaption(const QString &newCaption)
{
    m_caption = newCaption;
    ui->edtCaption->setText(m_caption);
}

int EditBalanceWheelItemDialog::score() const
{
    m_score=ui->edtScore->value();
    return m_score;
}

void EditBalanceWheelItemDialog::setScore(int newScore)
{
    m_score = newScore;
    ui->edtScore->setValue(m_score);
}

