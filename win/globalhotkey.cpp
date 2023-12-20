#include "globalhotkey.h"
#include "qwidget.h"
#include <minwindef.h>

GlobalHotKey::GlobalHotKey(QWidget* parent)
    : QWidget{parent}
{
    m_hwnd = (HWND)winId();

}

const QString& GlobalHotKey::hotKeyName() const
{
    return m_hotKeyName;
}

void GlobalHotKey::setHotKeyName(const QString& newHotKeyName)
{
    m_hotKeyName = newHotKeyName;
    ATOM tmpAtom = GlobalFindAtom(m_hotKeyName.toStdWString().data());
    if (tmpAtom == 0)
    {
        m_atom = GlobalAddAtom(m_hotKeyName.toStdWString().data());
    }
}

bool GlobalHotKey::registerHotkey(UINT fsModifiers, UINT vk)
{
    bool ret =  RegisterHotKey(m_hwnd, m_atom, fsModifiers, vk);
    qDebug() << ret;
    return ret;

}

HWND GlobalHotKey::hwnd() const
{
    return m_hwnd;
}

void GlobalHotKey::setHwnd(HWND newHwnd)
{
    m_hwnd = newHwnd;
}

void GlobalHotKey::deleteAtom()
{
    GlobalDeleteAtom(m_atom);

}

bool GlobalHotKey::nativeEvent(const QByteArray& eventType, void* message, long* result)
{

    MSG* winMsg = static_cast<MSG*>(message);
    if (winMsg->message == WM_HOTKEY)
    {
        emit procHotkey();
        return false;
    }
    return QWidget::nativeEvent(eventType, message, result);

}
