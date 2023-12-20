#include "linearequation.h"
#include "qdebug.h"

LinearEquation::LinearEquation(QObject *parent)
    : QObject{parent}
{

}

bool LinearEquation::getLinearEquationParams(double x1, double y1, double x2, double y2, double &a, double &b)
{
    a=(y1-y2)/(x1-x2);
    b=y1-a*x1;

    return true;

}

void LinearEquation::getLinearEquationValues(double x1, double y1, double x2, double y2, LinearEquationValues &values)
{
    double a,b;
    getLinearEquationParams(x1,y1,x2,y2,a,b);
    qDebug()<<a<<b;
    if (x1<=x2)
    {
        for (int i=x1;i<=x2;i++)
        {
            double y=a*i+b;
            QPair<double,double> p(i,y);
            values<<p;
        }
    }else
    {
        for (int i=x1;i>=x2;i--)
        {
            double y=a*i+b;
            QPair<double,double> p(i,y);
            values<<p;
        }
    }


}

bool LinearEquation::isTowLineIntersected(double ax1, double ay1, double ax2, double ay2, double bx1, double by1, double bx2, double by2, double &x, double &y)
{
    LinearEquationValues values1,values2;
    getLinearEquationValues(ax1,ay1,ax2,ay2,values1);
    getLinearEquationValues(bx1,by1,bx2,by2,values2);
    for( auto &v1:values1)
    {
        if(values2.contains(v1))
        {
            x=v1.first;
            y=v1.second;
            return true;
        }
    }



    return false;

}


