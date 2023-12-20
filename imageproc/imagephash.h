#ifndef IMAGEPHASH_H
#define IMAGEPHASH_H

#include <QObject>
#include <QDebug>
#include "opencv2/opencv.hpp"
using namespace cv;

class ImagePHash : public QObject
{
    Q_OBJECT
public:
    explicit ImagePHash(QObject* parent = nullptr);
    void loadFromFile(QString path);

    const QString& hashValue() const;
    void setHashValue(const QString& newHashValue);

signals:
private:
    QString m_hashValue;

};
int hamingDist(QString& s1, QString& s2);

#endif // IMAGEPHASH_H
