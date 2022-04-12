#ifndef HARDDECISION1507_H
#define HARDDECISION1507_H

#include <QStringList>

class HardDecision1507
{
public:
    int** A;
    int   n;
    HardDecision1507();
    void parseInput(QStringList input);
    void printMatrix();
    bool computeB();
    void Test1();
    void Test2();
};

#endif // HARDDECISION1507_H
