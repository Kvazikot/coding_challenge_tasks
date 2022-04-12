#ifndef HANOITOWER1054_H
#define HANOITOWER1054_H

#include <QString>
#include <vector>

class HanoiTower1054
{
public:
    std::vector<int> Dtarget, D;
    int Nmove;
    std::vector<std::vector<int> > pegs;
    HanoiTower1054(QString input);
    int printD(int N);
    void Hanoi(int N, int From, int To_, int Temp);
};

#endif // HANOITOWER1054_H
