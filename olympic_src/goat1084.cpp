#define _USE_MATH_DEFINES
//http://acm.timus.ru/problem.aspx?space=1&num=1084
#include <QDebug>
#include <math.h>
#include "goat1084.h"

float integral(float a, float R)
{
    float dx = 0.001;
    float sum = 0;
    float y=0;
    for(float x = -a; x < a; x+=dx)
    {
        y = sqrt(R*R-x*x);
        if( y > a)
          sum+=(y-a)*dx;
    }
    return sum;
}

Goat1084::Goat1084(float a, float b)
{
    float SquareRound = b * b * M_PI;
    float Scap = (integral(a / 2, b) ) ;
    float S = SquareRound - 4 * Scap;
    qDebug() << "Goat1084 " << a << " " << b;
    qDebug() << S;
}
