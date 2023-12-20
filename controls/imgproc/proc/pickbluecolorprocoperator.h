#ifndef PICKBLUECOLORPROCOPERATOR_H
#define PICKBLUECOLORPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class PickBlueColorProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit PickBlueColorProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // PICKBLUECOLORPROCOPERATOR_H
