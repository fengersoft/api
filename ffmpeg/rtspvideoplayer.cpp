#include "rtspvideoplayer.h"
#include "ui_rtspvideoplayer.h"

RtspVideoPlayer::RtspVideoPlayer(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::RtspVideoPlayer)
{
    ui->setupUi(this);
    m_thread = new RtspVideoPlayerThread(this);
    connect(m_thread, &RtspVideoPlayerThread::getFrame, this, &RtspVideoPlayer::onGetFrame);
    m_pause = false;
    m_isMax = false;
}

RtspVideoPlayer::~RtspVideoPlayer()
{

    m_thread->setCanStop(true);
    m_thread->msleep(3000);
    m_thread->quit();
    m_thread->wait();

    delete ui;
}

void RtspVideoPlayer::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, this->width(), this->height()); //先画成白色

    if (m_srcImage.size().width() <= 0)
        return;

    ///将图像按比例缩放成和窗口一样大小
    QImage img = m_srcImage.scaled(this->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int x = this->width() - img.width();
    int y = this->height() - img.height();

    x /= 2;
    y /= 2;

    painter.drawImage(QPoint(x, y), img); //画出图像

}

QString RtspVideoPlayer::rtspUrl() const
{
    return m_rtspUrl;
}

void RtspVideoPlayer::setRtspUrl(const QString& newRtspUrl)
{
    m_rtspUrl = newRtspUrl;
    m_thread->setRtspUrl(m_rtspUrl);
}

void RtspVideoPlayer::startPlay()
{
    m_thread->startPlay();

}

void RtspVideoPlayer::onGetFrame(QImage image)
{
    m_srcImage = image;
    update();

}

QRect RtspVideoPlayer::oldGeometry() const
{
    return m_oldGeometry;
}

void RtspVideoPlayer::setOldGeometry(const QRect& newOldGeometry)
{
    m_oldGeometry = newOldGeometry;
}

bool RtspVideoPlayer::isMax() const
{
    return m_isMax;
}

void RtspVideoPlayer::setIsMax(bool newIsMax)
{
    m_isMax = newIsMax;
}

void RtspVideoPlayer::mouseDoubleClickEvent(QMouseEvent* event)
{
    m_isMax = !m_isMax;
    if (m_isMax)
    {
        m_oldGeometry = this->geometry();
        emit showMax();
    }
    else
    {
        setGeometry(m_oldGeometry);
    }

}

bool RtspVideoPlayer::pause() const
{
    return m_pause;
}

void RtspVideoPlayer::setPause(bool newPause)
{
    m_pause = newPause;
    if (m_pause)
    {
        m_thread->pause();
    }
    else
    {
        m_thread->resume();
    }
}

void RtspVideoPlayer::autoChangePlayState()
{
    setPause(!pause());

}
