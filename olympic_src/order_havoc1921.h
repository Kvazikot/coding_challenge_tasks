#ifndef ORDER_HAVOC1921_H
#define ORDER_HAVOC1921_H

#include <vector>
#include <QString>


class order_havoc1921
{
    void ParseInput(QString input);
    void InitCells(int n, int m);
    void ClearCells(int n, int m);
    void Generate();
    char makeRandChar(int k);
    void Print();
    bool CheckRows();
    bool CheckCols();
    bool CheckDiogonal();
    char** cells;
    int n,m,k,l;
public:
    order_havoc1921();

};

#endif // ORDER_HAVOC1921_H
