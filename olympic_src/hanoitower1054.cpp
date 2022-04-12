#include "hanoitower1054.h"
#include <QStringList>
#include <QDebug>

void HanoiTower1054::Hanoi(int N, int From, int To_, int Temp)
{
    if( N>0 )
    {
        Hanoi(N-1, From, Temp, To_);
        //qDebug() << "N=" << N << " " << From << " " << To_ << " " << Temp;
        int d = pegs[From-1].back();
        pegs[From-1].pop_back();
        pegs[To_-1].push_back(d);
        Nmove++;
        if( printD(Nmove) )
            return;
        Hanoi(N-1, Temp, To_, From);
    }
}

int HanoiTower1054::printD(int N)
{
    for(int i=0; i < pegs.size(); i++)
        for(int j=0; j < pegs[i].size(); j++)
    {
            D[pegs[i][j]-1] = i+1;
    }
//    QString out;
//    for(int i=0; i < D.size(); i++)
//        out+=QString::number(D[i])+",";
//    qDebug() << out;
    bool isTargetD=true;
    for(int i=0; i < D.size(); i++)
        if(Dtarget[i]!=D[i])
            isTargetD = false;
    if( isTargetD )
    {
        qDebug() << "====> N=" << N;
        return 1;
    }
    return 0;

}

HanoiTower1054::HanoiTower1054(QString input)
{
    QStringList lines = input.split(",");
    int N = lines[0].toInt();
    for(int i=0; i < N; i++ )
        Dtarget.push_back(lines[i+1].toInt());

    Nmove = 0;
    pegs.push_back(std::vector<int>());
    pegs.push_back(std::vector<int>());
    pegs.push_back(std::vector<int>());
    pegs[0].push_back(3);
    pegs[0].push_back(2);
    pegs[0].push_back(1);
    D.push_back(1);
    D.push_back(1);
    D.push_back(1);
    Hanoi(3,1,2,3);
    qDebug();
}
