#ifndef IMAGETHEME_H
#define IMAGETHEME_H

#include <QObject>
#include "opencv2/opencv.hpp"
#include <QMap>
#include <QDebug>
using namespace cv;

class ImageTheme : public QObject
{
    Q_OBJECT
public:
    explicit ImageTheme(QObject* parent = nullptr);
    bool loadFromFile(QString filePath);
    QString themeNames(int len = 2);

signals:
private:
    QMap<QString, int> m_colors;
};

#endif // IMAGETHEME_H
