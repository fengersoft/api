#ifndef MAKEAREAHDIMAGEPROCOPERATOR_H
#define MAKEAREAHDIMAGEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"
class MakeAreaHdImageProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit MakeAreaHdImageProcOperator(QObject* parent = nullptr);
public:
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);

signals:

};

#endif // MAKEAREAHDIMAGEPROCOPERATOR_H
