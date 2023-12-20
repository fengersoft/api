#ifndef CHANGEPERSONPHOTOBACKGROUD_H
#define CHANGEPERSONPHOTOBACKGROUD_H

#include <QObject>
#include <QDebug>
#include "opencv2/opencv.hpp";

using namespace cv;

class ChangePersonPhotoBackgroud : public QObject
{
    Q_OBJECT
public:
    explicit ChangePersonPhotoBackgroud(QObject *parent = nullptr);

    const QString &srcPath() const;
    void setSrcPath(const QString &newSrcPath);

    const QString &destPath() const;
    void setDestPath(const QString &newDestPath);
    void convert();

signals:
private:
    QString m_srcPath;
    QString m_destPath;


};

#endif // CHANGEPERSONPHOTOBACKGROUD_H
