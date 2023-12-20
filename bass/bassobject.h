#ifndef BASSOBJECT_H
#define BASSOBJECT_H

#include <QObject>
#include <windef.h>
#include "bass.h"
#include <QDebug>
class BassObject : public QObject
{
    Q_OBJECT
public:
    explicit BassObject(QObject* parent = nullptr);

    HWND handle() const;
    void setHandle(HWND newHandle);
    void playMusic(QString path);


signals:

private:
    HWND m_handle;

};

#endif // BASSOBJECT_H
