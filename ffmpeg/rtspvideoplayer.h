#ifndef RTSPVIDEOPLAYER_H
#define RTSPVIDEOPLAYER_H

#include <QWidget>
#include <QPainter>
#include "rtspvideoplayerthread.h"


namespace Ui
{
class RtspVideoPlayer;
}

class RtspVideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit RtspVideoPlayer(QWidget* parent = nullptr);
    ~RtspVideoPlayer();
    void paintEvent(QPaintEvent* event);
    QString rtspUrl() const;
    void setRtspUrl(const QString& newRtspUrl);
    void startPlay();
    bool pause() const;
    void setPause(bool newPause);
    void autoChangePlayState();

    bool isMax() const;
    void setIsMax(bool newIsMax);
    QRect oldGeometry() const;
    void setOldGeometry(const QRect& newOldGeometry);

signals:
    void showMax();
protected:
    void mouseDoubleClickEvent(QMouseEvent* event);
public slots:
    void onGetFrame(QImage image);
private:
    Ui::RtspVideoPlayer* ui;
    QString m_rtspUrl;
    RtspVideoPlayerThread* m_thread;
    QImage m_srcImage;
    bool m_pause;
    bool m_isMax;
    QRect m_oldGeometry;


};

#endif // RTSPVIDEOPLAYER_H
