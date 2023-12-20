#ifndef GLOBALHOTKEY_H
#define GLOBALHOTKEY_H

#include "qobjectdefs.h"
#include "qwidget.h"
#include <QObject>
#include <minwindef.h>
#include <windef.h>
#include <windows.h>
#include <QWidget>
#include <QDebug>
class GlobalHotKey : public QWidget
{
    Q_OBJECT
public:
    explicit GlobalHotKey(QWidget* parent = nullptr);

    const QString& hotKeyName() const;
    void setHotKeyName(const QString& newHotKeyName);
    bool registerHotkey(UINT fsModifiers, UINT vk);

    HWND hwnd() const;
    void setHwnd(HWND newHwnd);
    void deleteAtom();
signals:
    void procHotkey();
protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);

signals:
private:
    QString m_hotKeyName;
    ATOM m_atom;
    HWND m_hwnd;

};

#endif // GLOBALHOTKEY_H
