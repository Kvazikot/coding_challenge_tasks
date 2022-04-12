#include <QDebug>
#include <QStringList>
#include "sacramentsun1021.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

SacramentSun1021::SacramentSun1021(QString input)
{
    QStringList lines = input.split(",");
    int N1 = lines[0].toInt();
    int N2 = lines[N1+1].toInt();
    for(int i=1; i < N1+1; i++)
        A.push_back( lines[i].toInt() );
    for(int i=N1+2; i < N1+N2+2; i++)
        B.push_back( lines[i].toInt() );
    auto t1 = Clock::now();
    findPairs1();
    auto t2 = Clock::now();

    qDebug() << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" ;

    t1 = Clock::now();
    findPairs2();
    t2 = Clock::now();
    qDebug() << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" ;

    t1 = Clock::now();
    findPairs3();
    t2 = Clock::now();
    qDebug() << "Delta t2-t1: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" ;

    qDebug();
}

void SacramentSun1021::findPairs2()
{
    std::map<int,int> map;
    for(int i=0; i < A.size(); i++)
        map[(10000 - A[i])] = A[i];
    for(int i=0; i < B.size(); i++)
    {
        std::map<int,int>::iterator it;
        it = map.find(B[i]);
        if(it!=map.end())
        {
            qDebug() << it->first << "+" << it->second;
        }
    }
}

void SacramentSun1021::findPairs3()
{
    std::vector<int> C;
    for(int i=0; i < A.size(); i++)
        C.push_back((10000 - A[i]));
    std::sort(B.begin(), B.end(),
              [](const int  a, const int  b) -> bool
    {
              return a > b;
    });

    std::sort(C.begin(), C.end(),
              [](const int  a, const int  b) -> bool
    {
              return a > b;
    });

    for(int i=0; i < C.size(); i++)
    {
        for(int j=0; j < B.size(); j++)
        {
            if( C[i] == B[j])
            {
                qDebug() << A[i] << "+" << B[j];
            } else
                if(C[i] > B[j]) continue;
        }
    }


}

void SacramentSun1021::findPairs1()
{
    for(int i=0; i < A.size(); i++)
        for(int j=0; j < B.size(); j++)
        {
            if( (A[i] + B[j]) == 10000 )
            {
                qDebug() << A[i] << "+" << B[j];
            }
        }
}
