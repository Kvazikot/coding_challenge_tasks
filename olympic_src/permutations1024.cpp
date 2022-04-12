#include <QDebug>
#include <QStringList>
#include "permutations1024.h"
//http://acm.timus.ru/problem.aspx?space=1&num=1024

Permutations1024::Permutations1024(int n, QString input)
    :N(n)
{
    QStringList list = input.split(" ");
    QString s;
    for(int i=0; i < n; i++)
    {
        s = list[i];
        B.push_back(s.toInt());
        A.push_back(i+1);
    }
    PrintAB(A,B);
    DoPermutations();
}

bool Permutations1024::isEn()
{
    for(int i=0; i < N; i++)
        if( A[i] != B[i] ) return false;
    return true;
}

void Permutations1024::DoPermutations()
{
    int k=0;
    /*
    while( k < 4 )
    {
        std::vector<int> C;
        for(int i=0; i < N; i++)
        {
            C.push_back(B[B[i]-1]);
        }
        PrintAB(A,C);
        B = C;
        k++;
    }
    */
    while( !isEn() )
    {
       std::swap(*std::find(B.begin(),B.end(),k+1),B.at(k));
       PrintAB(A,B);
       k++;
    }
    qDebug() << "k=" << (k)*2;
}

void Permutations1024::PrintAB(std::vector<int>& AA, std::vector<int>& BB)
{
    QString out;
    QDebug dbg(&out);
    dbg << "=====================";
    dbg << "\n";
    for(int i=0; i < N; i++)
    {
        dbg << AA[i] << ",";
    }
    dbg << "\n";
    for(int i=0; i < N; i++)
    {
        dbg << BB[i] << ",";
    }

    qDebug() << out;

}
