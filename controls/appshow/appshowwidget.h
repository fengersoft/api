#ifndef APPSHOWWIDGET_H
#define APPSHOWWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDesktopServices>
#include <QMouseEvent>
#include <QProcess>

#include "../api/controls/appshow/editappinfodialog.h"
#include "../api/controls/base/baseitem.h"
#include "../api/controls/base/widgethelper.h"

using AppShowWidgetItem=BaseItem;

namespace Ui {
class AppShowWidget;
}

class AppShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AppShowWidget(QWidget *parent = nullptr);
    ~AppShowWidget();
    void loadAppInfos();
    void saveAppInfos();

    const QString &configPath() const;
    void setConfigPath(const QString &newConfigPath);
    QList<AppShowWidgetItem*> m_items;
    const QList<AppShowWidgetItem *> &items() const;
    void setItems(const QList<AppShowWidgetItem *> &newItems);
    const QPixmap &backgroundImage() const;
    void setBackgroundImage(const QPixmap &newBackgroundImage);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
public slots:
    void onActionTriggered();
private:
    Ui::AppShowWidget *ui;
    QString m_configPath;
    WidgetHelper *m_helper;
    QPixmap m_backgroundImage;
    AppShowWidgetItem* m_selectItem;

};

#endif // APPSHOWWIDGET_H
