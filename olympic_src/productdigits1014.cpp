#include <QDebug>
#include "productdigits1014.h"
//http://acm.timus.ru/problem.aspx?space=1&num=1014

ProductDigits1014::ProductDigits1014(int N)
{
    N = 200;
    if(N > 10e9)
    {
        qDebug() << "value of N out of range!";
        return;
    }
    qDebug() << "N = " << N << " Q = " << findQ(N);
}

int ProductDigits1014::findQ(int N)
{
    int ost;
    std::vector<int> multipliers;
    while( 1 )
    {
        bool found = false;
        for(int i=9; i>=2; i--)
        {
            if(N % i == 0)
            {
                multipliers.push_back(i);
                N = N / i;
                found = true;
                break;
            }
        }
        if( !found && N!=1 )
        {
            return -1;
        }
        if(  N == 1 ) break;

    }
    std::sort(multipliers.begin(), multipliers.end(),
        [](const int  a, const int  b) -> bool
    {
         return a < b;
    });

     QString out;
     for(auto i=0; i < multipliers.size(); i++)
       out+=QString::number(multipliers[i]);

     return out.toInt();

}
