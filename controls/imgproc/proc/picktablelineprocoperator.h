#ifndef PICKTABLELINEPROCOPERATOR_H
#define PICKTABLELINEPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class PickTableLineProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit PickTableLineProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
signals:

};

#endif // PICKTABLELINEPROCOPERATOR_H
