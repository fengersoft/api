
#include "rtspvideoplayerthread.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/pixfmt.h"
#include "libswscale/swscale.h"
}

#include <stdio.h>
#include<iostream>

using namespace std;
RtspVideoPlayerThread::RtspVideoPlayerThread(QObject* parent): QThread(parent)
{

    qDebug() << "RtspVideoPlayerThread::RtspVideoPlayerThread()";


}

RtspVideoPlayerThread::~RtspVideoPlayerThread()
{
    qDebug() << "RtspVideoPlayerThread::~RtspVideoPlayerThread()";
}

void RtspVideoPlayerThread::startPlay()
{
    ///调用 QThread 的start函数 将会自动执行下面的run函数 run函数是一个新的线程
    this->start();

}

void RtspVideoPlayerThread::run()
{
    qDebug() << "void RtspVideoPlayerThread::run()";
    AVFormatContext* pFormatCtx;
    AVCodecContext* pCodecCtx;
    AVCodec* pCodec;
    AVFrame* pFrame, *pFrameRGB;
    AVPacket* packet;
    uint8_t* out_buffer;

    static struct SwsContext* img_convert_ctx;

    int videoStream, i, numBytes;
    int ret, got_picture;

    avformat_network_init();   ///初始化FFmpeg网络模块，2017.8.5---lizhen
    av_register_all();         //初始化FFMPEG  调用了这个才能正常适用编码器和解码器


    //Allocate an AVFormatContext.
    pFormatCtx = avformat_alloc_context();

    ///2017.8.5---lizhen
    AVDictionary* avdic = 0;
    // 设置缓存大小 1024000byte
    av_dict_set(&avdic, "buffer_size", "1024000", 0);
    // 设置超时时间 20s
    av_dict_set(&avdic, "stimeout", "20000000", 0);
    // 设置最大延时 3s
    av_dict_set(&avdic, "max_delay", "30000000", 0);
    // 设置打开方式 tcp/udp
    av_dict_set(&avdic, "rtsp_transport", "tcp", 0);

    ///rtsp地址，可根据实际情况修改
    char url[256] = {0};
    memcpy(url, m_rtspUrl.toStdString().data(), strlen(m_rtspUrl.toStdString().data()));

    ret = avformat_open_input(&pFormatCtx, url, NULL, &avdic);
    if (ret < 0)
    {
        char temp[30] = {0};
        av_strerror(ret, temp, 30);
        qDebug() << QString::fromLocal8Bit(temp);
        qDebug() << "can't open the file. \n";

        printf("can't open the file. \n");
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        printf("Could't find stream infomation.\n");
        return;
    }

    videoStream = -1;

    ///循环查找视频中包含的流信息，直到找到视频类型的流
    ///便将其记录下来 保存到videoStream变量中
    ///这里我们现在只处理视频流  音频流先不管他
    for (i = 0; i < pFormatCtx->nb_streams; i++)
    {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
        }
    }


    ///如果videoStream为-1 说明没有找到视频流
    if (videoStream == -1)
    {
        printf("Didn't find a video stream.\n");
        return;
    }

    ///查找解码器
    pCodecCtx = pFormatCtx->streams[videoStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    ///2017.8.9---lizhen
    pCodecCtx->bit_rate = 0;  //初始化为0
    pCodecCtx->time_base.num = 1; //下面两行：一秒钟25帧
    pCodecCtx->time_base.den = 10;
    pCodecCtx->frame_number = 1; //每包一个视频帧

    if (pCodec == NULL)
    {
        qDebug() << "Codec not found.\n";
        return;
    }

    ///打开解码器
    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
    {
        printf("Could not open codec.\n");
        //QMessageBox::information(nullptr, "tip", "Could not open codec.\n");
        return;
    }

    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();

    ///这里我们改成了 将解码后的YUV数据转换成RGB32
    img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height,
                                     pCodecCtx->pix_fmt, pCodecCtx->width, pCodecCtx->height,
                                     AV_PIX_FMT_RGBA, SWS_FAST_BILINEAR, NULL, NULL, NULL);

    numBytes = avpicture_get_size(AV_PIX_FMT_RGBA, pCodecCtx->width, pCodecCtx->height);

    out_buffer = (uint8_t*) av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture*) pFrameRGB, out_buffer, AV_PIX_FMT_RGBA,
                   pCodecCtx->width, pCodecCtx->height);

    int y_size = pCodecCtx->width * pCodecCtx->height;

    packet = (AVPacket*) malloc(sizeof(AVPacket));  //分配一个packet
    av_new_packet(packet, y_size); //分配packet的数据
    m_canStop = false;
    while (1)
    {
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //这里认为视频读取完了
        }

        if (packet->stream_index == videoStream)
        {
            ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);

            if (ret < 0)
            {
                printf("decode error.\n");
                return;
            }

            if (got_picture)
            {
                sws_scale(img_convert_ctx,
                          (uint8_t const * const*) pFrame->data,
                          pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                          pFrameRGB->linesize);
                //把这个RGB数据 用QImage加载
                QImage tmpImg((uchar*)out_buffer, pCodecCtx->width, pCodecCtx->height, QImage::Format_RGBA8888);

                //QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
                emit getFrame(tmpImg);  //发送信号
                ///2017.8.11---lizhen

            }
        }
        av_free_packet(packet); //释放资源,否则内存会一直上升

        ///2017.8.7---lizhen
        msleep(1); //停一停  不然放的太快了
        if (m_canStop == true)
        {
            break;
        }
        if (m_pause)
        {
            m_mutex.lock();
            m_waitCon.wait(&m_mutex);
            m_mutex.unlock();
        }

    }
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    qDebug() << "end";

}

bool RtspVideoPlayerThread::canStop() const
{
    return m_canStop;
}

void RtspVideoPlayerThread::setCanStop(bool newCanStop)
{
    m_canStop = newCanStop;
}

void RtspVideoPlayerThread::pause()
{
    m_mutex.lock();
    m_pause = true;
    m_mutex.unlock();

}

void RtspVideoPlayerThread::resume()
{
    m_mutex.lock();
    m_pause = false;
    m_waitCon.wakeAll();
    m_mutex.unlock();

}

QString RtspVideoPlayerThread::rtspUrl() const
{
    return m_rtspUrl;
}

void RtspVideoPlayerThread::setRtspUrl(const QString& newRtspUrl)
{
    m_rtspUrl = newRtspUrl;
}
