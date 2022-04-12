// http://acm.timus.ru/problem.aspx?space=1&num=1068
#include <QDebug>
#include "sum1068.h"
#include <math.h>

Sum1068::Sum1068(int N)
{
    if( abs(N) > 100000 )
        qDebug() << "input greater than 10000";


    int sum=0;
    if( N > 0)
    {
        for(int i=1; i <= N; i++)
        {
            sum+=i;
        }
    }
    else
    {
        for(int i=N; i <= 1; i++)
        {
            sum+=i;
        }

    }
    qDebug() << "input \t" << "output";
    qDebug() << N << "\t" << sum;
}
