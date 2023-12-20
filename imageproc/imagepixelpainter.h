#ifndef IMAGEPIXELPAINTER_H
#define IMAGEPIXELPAINTER_H

#include <QObject>
#include <QImage>
#include <QPainter>
#include <QDebug>

class ImagePixelPainter : public QObject
{
    Q_OBJECT
public:
    explicit ImagePixelPainter(QObject *parent = nullptr);

    const QString &srcPath() const;
    void setSrcPath(const QString &newSrcPath);

    const QString &destPath() const;
    void setDestPath(const QString &newDestPath);
    void convert();


    int colorStep() const;
    void setColorStep(int newColorStep);

signals:
private:
    QString m_srcPath;
    QString m_destPath;
    int m_colorStep;

};

#endif // IMAGEPIXELPAINTER_H
