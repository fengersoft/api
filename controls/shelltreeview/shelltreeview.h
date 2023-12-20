#ifndef SHELLTREEVIEW_H
#define SHELLTREEVIEW_H

#include "qfileinfo.h"
#include "qobjectdefs.h"
#include "qset.h"
#include "qstandarditemmodel.h"
#include <QWidget>
#include <QStandardItemModel>
#include <QDir>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QDebug>
#include <QKeyEvent>
#include <QAction>
#include <QDesktopServices>

namespace Ui
{
class ShellTreeView;
}

class ShellTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit ShellTreeView(QWidget* parent = nullptr);
    ~ShellTreeView();

    const QString& rootPath() const;
    void setRootPath(const QString& newRootPath);
    void refreshTreeView();
    void addChildFile(QString parentPath, QStandardItem* parentNode);
signals:
    void clickNode(QFileInfo& info);
protected:
    void keyPressEvent(QKeyEvent* event);
private slots:
    void on_tvData_clicked(const QModelIndex& index);

    void on_tvData_expanded(const QModelIndex& index);
    void onTriggered(bool checked = false);

private:
    Ui::ShellTreeView* ui;
    QString m_rootPath;
    QStandardItemModel* m_model;
    QSet<QString> m_expandDirs;
};

#endif // SHELLTREEVIEW_H
