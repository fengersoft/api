#ifndef REMOVESELSTAINSPROCOPERATOR_H
#define REMOVESELSTAINSPROCOPERATOR_H

#include <QObject>
#include "abstractimageprocoperator.h"

class RemoveSelStainsProcOperator : public AbstractImageProcOperator
{
    Q_OBJECT
public:
    explicit RemoveSelStainsProcOperator(QObject* parent = nullptr);
    void operatorImage(Mat& src, Mat& dest, ImageProcInfo& info);
    void removeStains(Mat& imgData, int x, int y, int w, int h, ImageProcInfo& info);
    inline bool isHdBackColor(int r, int g, int b);
signals:

};

#endif // REMOVESELSTAINSPROCOPERATOR_H
