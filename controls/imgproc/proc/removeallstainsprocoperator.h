#ifndef REMOVEALLSTAINSPROCOPERATOR_H
#define REMOVEALLSTAINSPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class RemoveAllStainsProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit RemoveAllStainsProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
    void removeStains(Mat& imgData, int x, int y, int w, int h, ImageProcInfo& info);
    inline bool isHdBackColor(int r, int g, int b);
signals:

};

#endif // REMOVEALLSTAINSPROCOPERATOR_H
