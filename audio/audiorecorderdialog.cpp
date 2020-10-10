#include "audiorecorderdialog.h"
#include "ui_audiorecorderdialog.h"

AudioRecorderDialog::AudioRecorderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AudioRecorderDialog)
{
    ui->setupUi(this);
}

AudioRecorderDialog::~AudioRecorderDialog()
{
    delete ui;
}
