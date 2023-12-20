#include "bassobject.h"
#include "bass.h"
#include <winnt.h>

BassObject::BassObject(QObject* parent)
    : QObject{parent}
{



}

HWND BassObject::handle() const
{
    return m_handle;
}

void BassObject::setHandle(HWND newHandle)
{
    m_handle = newHandle;
    // initialize default output device
    if (!BASS_Init(-1, 44100, 0, 0, NULL))
    {
        qDebug() << "Can't initialize device";
        return;
    }
    else
    {
        qDebug() << "initialize device";
    }
    BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, 10000);

}

void BassObject::playMusic(QString path)
{
    qDebug() << path;

    int Init = BASS_StreamCreateFile(FALSE, path.toStdString().c_str(), 0, 0, 0); //得到流句柄
    qDebug() << "init:" << Init;
    BASS_ChannelPlay(Init, TRUE); //播放
}
