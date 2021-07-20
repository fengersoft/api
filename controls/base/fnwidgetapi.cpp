#include "fnwidgetapi.h"


void addWidgetToPage(QWidget* parent, QWidget* child)
{

    QHBoxLayout* lay = new QHBoxLayout();
    parent->setLayout(lay);
    lay->setMargin(0);
    lay->addWidget(child);

}
