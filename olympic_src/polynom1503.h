#ifndef POLYNOM1503_H
#define POLYNOM1503_H

#include <vector>
#include <QStringList>
#include <QTextStream>

class Polynom1503
{
public:
    QTextStream dbg_stream;
    double dummy;
    Polynom1503();
    std::vector<float> scanForRoots(float* a, float x1, float x2, float dx);
    void parseInput(QStringList input);
    void TestRootFinding1();
    void TestRootFinding2();
    void TestPolyFAndRt();

    int n;
    float* a;

};

#endif // POLYNOM1503_H
