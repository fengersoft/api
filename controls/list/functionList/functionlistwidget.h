#ifndef FUNCTIONLISTWIDGET_H
#define FUNCTIONLISTWIDGET_H

#include <QWidget>
#include "functionlist.h"
#include "../../base/fnwidgetapi.h"

namespace Ui
{
class FunctionListWidget;
}

class FunctionListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionListWidget(QWidget* parent = nullptr);
    ~FunctionListWidget();

    FunctionList* list() const;
    void setList(FunctionList* newList);

private slots:
    void on_edtSearch_textChanged(const QString& arg1);

private:
    Ui::FunctionListWidget* ui;
    FunctionList* m_list;
};

#endif // FUNCTIONLISTWIDGET_H
