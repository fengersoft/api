/**
 * 李震
 * 我的码云：https://git.oschina.net/git-lizhen
 * 我的CSDN博客：http://blog.csdn.net/weixin_38215395
 * 联系：QQ1039953685
 */

#ifndef RTSPVIDEOPLAYERTHREAD_H
#define RTSPVIDEOPLAYERTHREAD_H

#include <QThread>
#include <QImage>
#include <QDebug>
#include <QWaitCondition>
#include <QMutex>



class RtspVideoPlayerThread : public QThread
{
    Q_OBJECT

public:
    explicit RtspVideoPlayerThread(QObject* parent = nullptr);

    ~RtspVideoPlayerThread();

    void startPlay();

    QString rtspUrl() const;
    void setRtspUrl(const QString& newRtspUrl);

    bool canStop() const;
    void setCanStop(bool newCanStop);
    void pause();
    void resume();

signals:
    void getFrame(QImage); //每获取到一帧图像 就发送此信号


protected:
    void run();

private:
    QString mFileName;
    QString m_rtspUrl;
    bool m_canStop;
    bool m_pause = false;
    QMutex m_mutex;
    QWaitCondition m_waitCon;


};

#endif // RTSPVIDEOPLAYERTHREAD_H
