#ifndef RAILWAYTICKETS1031_H
#define RAILWAYTICKETS1031_H

#include <QString>
#include <vector>

class RailwayTickets1031
{
public:
    RailwayTickets1031(QString input);
    bool checkInput();
    int  calcPrice();
    int  getPriceByDist(int d);
protected:
    int L1, L2, L3, C1, C2, C3;
    int N;
    int n1,n2;
    std::vector<int> dist;

};

#endif // RAILWAYTICKETS1031_H
