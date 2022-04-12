#include <QStringList>
#include <QDebug>
#include "harddecision1507.h"

HardDecision1507::HardDecision1507()
{
    Test1();
    Test2();
}

void HardDecision1507::Test2()
{
    QStringList input;

    input.push_back("3");
    input.push_back("100 35 40");
    input.push_back("0 22 0");
    input.push_back("10 11 0");
    parseInput(input);
    printMatrix();
    if( computeB() )
        qDebug() << "yes";
    else
        qDebug() << "no";

}

void HardDecision1507::Test1()
{
    QStringList input;

    input.push_back("2");
    input.push_back("0 7");
    input.push_back("15 30");

    parseInput(input);
    printMatrix();
    if( computeB() )
        qDebug() << "yes";
    else
        qDebug() << "no";

}

void HardDecision1507::printMatrix()
{
    for(int j=0; j < n; j++)
    {
        QString line;
        for(int i=0; i < n; i++)
            line+=QString::number(A[j][i])+" ";
        qDebug() << line;
    }
}

bool HardDecision1507::computeB()
{
    for(int i=1; i <= n; i++)
    {
        int k1 = i * (i-1);
        int k2 = i * (i+1);
        int sum=0;
        for(int k=k1; k!=k2; k++)
        {
            int ii = (k-1) / n;
            int jj = (k-1) % n;
            if( ii < 0) continue;
            if( jj < 0) continue;
            if( ii >= n) continue;
            if( jj >= n) continue;
            sum+=A[ii][jj];
            if(sum > 0) break;
        }
        if(sum==0) return false;
    }
    return true;
}

void HardDecision1507::parseInput(QStringList input)
{
    n = input[0].toInt();
    A = new int*[n];

    for(int j=0; j < n; j++)
    {
        A[j] = new int[n];
        QStringList line = input[j+1].split(" ");
        if( line.size()!=n )
        {
            qDebug() << "Error parsing input!";
            return;
        }
        for(int i=0; i < n; i++)
        {
            A[j][i] = line[i].toInt();
        }
    }
}
