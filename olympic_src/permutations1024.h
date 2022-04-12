#ifndef PERMUTATIONS1024_H
#define PERMUTATIONS1024_H

#include <QString>
#include <vector>
class Permutations1024
{
public:
    std::vector<int> A,B;
    int N;
    Permutations1024(int n, QString input);
    void PrintAB(std::vector<int>& A, std::vector<int>& B);
    void DoPermutations();
    bool isEn();
};

#endif // PERMUTATIONS1024_H
