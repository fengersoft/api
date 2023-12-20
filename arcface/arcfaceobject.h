#ifndef ARCFACEOBJECT_H
#define ARCFACEOBJECT_H

#include <QObject>
#include "arcsoft_face_sdk.h"
#include "merror.h"
#include "opencv2/opencv.hpp"
#include <QDebug>
using namespace cv;



class ArcFaceObject : public QObject
{
    Q_OBJECT
public:
    explicit ArcFaceObject(QObject* parent = nullptr);
    void loadFromFile(QString path);
    const QString& appKey() const;
    void setAppKey(const QString& newAppKey);

    const QString& sdkKey() const;
    void setSdkKey(const QString& newSdkKey);

    bool hasFace() const;
    void setHasFace(bool newHasFace);

    const QString& versionInfo() const;
    void setVersionInfo(const QString& newVersionInfo);

signals:
private:
    QString m_appKey;
    QString m_sdkKey;
    bool m_hasFace;
    QString m_versionInfo;

};

bool hasFaceInImage(QString path);

#endif // ARCFACEOBJECT_H
