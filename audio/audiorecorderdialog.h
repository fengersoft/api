#ifndef AUDIORECORDERDIALOG_H
#define AUDIORECORDERDIALOG_H

#include <QDialog>

namespace Ui {
class AudioRecorderDialog;
}

class AudioRecorderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AudioRecorderDialog(QWidget *parent = nullptr);
    ~AudioRecorderDialog();

private:
    Ui::AudioRecorderDialog *ui;
};

#endif // AUDIORECORDERDIALOG_H
