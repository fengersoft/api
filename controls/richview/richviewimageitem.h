#ifndef RICHVIEWIMAGEITEM_H
#define RICHVIEWIMAGEITEM_H

#include <QWidget>
#include <QPainter>
#include <QAction>
#include <QApplication>
#include <QClipboard>



namespace Ui
{
class RichViewImageItem;
}

class RichViewImageItem : public QWidget
{
    Q_OBJECT

public:
    explicit RichViewImageItem(QWidget* parent = nullptr);
    ~RichViewImageItem();
    QString filePath() const;
    void setFilePath(const QString& newFilePath);
    int imageHeight() const;
    void setImageHeight(int newImageHeight);

public slots:
    void onTriggered();
protected:
    void paintEvent(QPaintEvent* event);

private:
    Ui::RichViewImageItem* ui;
    QString m_filePath;
    QPixmap m_srcPix;
    mutable int m_imageHeight;
};

#endif // RICHVIEWIMAGEITEM_H
