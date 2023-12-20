#include "webimageviewer.h"
#include "ui_webimageviewer.h"

WebImageViewer::WebImageViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebImageViewer)
{
    ui->setupUi(this);
}

WebImageViewer::~WebImageViewer()
{
    delete ui;
}

bool WebImageViewer::loadFromUrl(QString url)
{
    m_url=url;
    QNetworkAccessManager *manager=new QNetworkAccessManager(nullptr);
    QNetworkRequest request;

    request.setUrl(QUrl(url));
    QNetworkReply* reply= manager->get(request);
    QEventLoop loop;
    connect(reply,&QNetworkReply::finished,&loop,&QEventLoop::quit);
    loop.exec();


    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (code==200)
    {
        QByteArray retData=reply->readAll();
        m_pix.loadFromData(retData);
        qDebug()<<m_pix.width()<<m_pix.height();
        update();
    }
    reply->deleteLater();
    delete manager;
    return code==200;

}

void WebImageViewer::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter;
    painter.begin(this);
    double f1=width();
    f1=f1/height();

    double f2=m_pix.width();
    f2=f2/m_pix.height();

    //等宽
    QPixmap tempPix;
    QRect drawRect;
    if (f1<f2)
    {
        tempPix=m_pix.scaledToWidth(width());

        drawRect=QRect(0,(height()-tempPix.height())/2,tempPix.width(),tempPix.height());


    }else
    {
        tempPix=m_pix.scaledToHeight(height());


         drawRect=QRect((width()-tempPix.width())/2,0,tempPix.width(),tempPix.height());
    }


    painter.drawRect(drawRect);
    painter.drawPixmap(drawRect,tempPix,tempPix.rect());
    painter.end();

}

const QString &WebImageViewer::url() const
{
    return m_url;
}

void WebImageViewer::setUrl(const QString &newUrl)
{
    m_url = newUrl;
}
