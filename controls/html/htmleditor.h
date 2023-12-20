#ifndef HTMLEDITOR_H
#define HTMLEDITOR_H

#include <QWidget>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QWebEngineSettings>
#include <QWebEnginePage>
#include <QFile>

#include "../api/controls/base/fnwidgetapi.h"


namespace Ui
{
class HtmlEditor;
}

class HtmlEditor : public QWidget
{
    Q_OBJECT

public:
    explicit HtmlEditor(QWidget* parent = nullptr);
    ~HtmlEditor();
    bool contentEditable() const;
    void setContentEditable(bool newContentEditable);
    void loadFromFile(QString path);
    void loadFromUrl(QString url);
    void saveToFile(QString path);
public slots:
    void onLoadProgress(int progress);
private:
    Ui::HtmlEditor* ui;
    QWebEngineView* m_view;
    bool m_contentEditable;
    QString m_path;
    QString m_savePath;
};

#endif // HTMLEDITOR_H
