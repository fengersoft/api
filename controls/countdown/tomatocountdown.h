#ifndef TOMATOCOUNTDOWN_H
#define TOMATOCOUNTDOWN_H

#include <QWidget>
#include "abstractcountdown.h"


namespace Ui
{
class TomatoCountdown;
}

class TomatoCountdown : public AbstractCountDown
{
    Q_OBJECT

public:
    explicit TomatoCountdown(QWidget* parent = nullptr);
    ~TomatoCountdown();
protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::TomatoCountdown* ui;
};

#endif // TOMATOCOUNTDOWN_H
