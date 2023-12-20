#include "shortcutitemwidget.h"
#include "qkeysequence.h"
#include "ui_shortcutitemwidget.h"

ShortCutItemWidget::ShortCutItemWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ShortCutItemWidget)
{
    ui->setupUi(this);

}

ShortCutItemWidget::~ShortCutItemWidget()
{
    delete ui;
}

const QString& ShortCutItemWidget::caption() const
{
    return m_caption;
}

void ShortCutItemWidget::setCaption(const QString& newCaption)
{
    m_caption = newCaption;
    ui->lblCaption->setText(m_caption + ":");

}

QString& ShortCutItemWidget::shortCut()
{
    m_shortCut = ui->edtShortcut->keySequence().toString();
    return m_shortCut;
}

void ShortCutItemWidget::setShortCut(const QString& newShortCut)
{
    m_shortCut = newShortCut;
    ui->edtShortcut->setKeySequence(QKeySequence(m_shortCut));
}

void ShortCutItemWidget::on_btnClear_clicked()
{
    ui->edtShortcut->clear();
}

