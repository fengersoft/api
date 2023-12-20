#ifndef WEBRICHEDIT_H
#define WEBRICHEDIT_H

#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QtWebEngineCore/QWebEngineSettings>

#include "../base/fnwidgetapi.h"

namespace Ui {
class WebRichEdit;
}

class WebRichEdit : public QWidget
{
    Q_OBJECT

public:
    explicit WebRichEdit(QWidget *parent = nullptr);
    ~WebRichEdit();

private:
    Ui::WebRichEdit *ui;
    QWebEngineView *m_viewer;
};

#endif // WEBRICHEDIT_H
