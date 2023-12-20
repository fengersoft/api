#ifndef IMAGEMAP_H
#define IMAGEMAP_H

#include <QObject>
#include <QMap>
#include <QImage>
#include <QDebug>
#include <QPixmap>

class ImageMap : public QObject
{
    Q_OBJECT
public:
    explicit ImageMap(QObject* parent = nullptr);
    void addImage(QString name, QString path, QColor color);
    QPixmap  pixmap(QString name);
signals:
private:
    QMap<QString, QPixmap> m_images;

};

#endif // IMAGEMAP_H
