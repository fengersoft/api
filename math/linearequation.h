#ifndef LINEAREQUATION_H
#define LINEAREQUATION_H

#include <QObject>
#include <QDebug>
using LinearEquationValues=QList<QPair<double,double> >;
class LinearEquation : public QObject
{
    Q_OBJECT
public:
    explicit LinearEquation(QObject *parent = nullptr);
    bool getLinearEquationParams(double x1,double y1,double x2,double y2,double &a,double &b);
    void getLinearEquationValues(double x1,double y1,double x2,double y2,LinearEquationValues &values);
    bool isTowLineIntersected(double ax1,double ay1,double ax2,double ay2,
                              double bx1,double by1,double bx2,double by2,
                              double &x,double &y);
signals:

};

#endif // LINEAREQUATION_H
