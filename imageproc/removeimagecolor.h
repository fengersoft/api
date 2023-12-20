#ifndef REMOVEIMAGECOLOR_H
#define REMOVEIMAGECOLOR_H

#include <QObject>
#include <QSet>
#include <QFile>
#include <QDebug>
#include <QColor>
#include "opencv2/opencv.hpp"
using namespace cv;
class RemoveImageColor : public QObject
{
    Q_OBJECT
public:
    explicit RemoveImageColor(QObject *parent = nullptr);

    const QString &src() const;
    void setSrc(const QString &newSrc);

    const QString &dest() const;
    void setDest(const QString &newDest);

    const QString &dataset() const;
    void setDataset(const QString &newDataset);
    void convert();
    int colorOffSet() const;
    void setColorOffSet(int newColorOffSet);

signals:
private:
    QString m_src;
    QString m_dest;
    QString m_dataset;
    int m_colorOffSet;
    QSet<int> m_dataColors;
    QSet<int> m_cacheColors;


};

#endif // REMOVEIMAGECOLOR_H
