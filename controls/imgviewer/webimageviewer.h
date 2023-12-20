#ifndef WEBIMAGEVIEWER_H
#define WEBIMAGEVIEWER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>
#include <QDebug>
#include <QPainter>

namespace Ui {
class WebImageViewer;
}

class WebImageViewer : public QWidget
{
    Q_OBJECT

public:
    explicit WebImageViewer(QWidget *parent = nullptr);
    ~WebImageViewer();
    bool loadFromUrl(QString url);
    const QString &url() const;
    void setUrl(const QString &newUrl);

protected:
    void paintEvent(QPaintEvent *event);


private:
    Ui::WebImageViewer *ui;
    QPixmap m_pix;
    QString m_url;
};

#endif // WEBIMAGEVIEWER_H
