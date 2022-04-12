#include <QDebug>
#include <QStringList>
#include "railwaytickets1031.h"
//http://acm.timus.ru/problem.aspx?space=1&num=1031

RailwayTickets1031::RailwayTickets1031(QString input)
{
    QStringList lines = input.split(",");
    QStringList parts = lines[0].split(" ");
    L1 = parts[0].toInt();
    L2 = parts[1].toInt();
    L3 = parts[2].toInt();
    C1 = parts[3].toInt();
    C2 = parts[4].toInt();
    C3 = parts[5].toInt();
    N = lines[1].toInt();
    parts = lines[2].split(" ");
    n1 = parts[0].toInt();
    n2 = parts[1].toInt();
    //n1 = 4;
    //n2 = 7;
    int last_dist = 0;
    for(int i=3; i < lines.size(); i++)
    {
        //dist.push_back(lines[i].toInt());
        dist.push_back(lines[i].toInt() - last_dist);
        last_dist = lines[i].toInt();
    }
    if( !checkInput() )
    {
        qDebug() << "check input please!";
        return;
    }
    qDebug() << "price from" << n1 << " to " << n2 << " is " << calcPrice();
}

bool RailwayTickets1031::checkInput()
{
    if(L1 > 10e9) return false;
    if(L2 > 10e9) return false;
    if(L3 > 10e9) return false;
    if(C1 > 10e9) return false;
    if(C2 > 10e9) return false;
    if(C3 > 10e9) return false;
    if( N < 2 || N > 10000) return false;
    return true;

}

int  RailwayTickets1031::getPriceByDist(int d)
{
    if( d > 0 && d <= L1 ) return C1;
    if( d > L1 && d <= L2 ) return C2;
    if( d > L2 && d <= L3 ) return C3;
    return -1;

}

int  RailwayTickets1031::calcPrice()
{
    int d,price=0;
    int n = n1;
    int sum = 0;
    int sum_prev = 0;
    while( n != n2 )
    {
        d = dist[n-1];
        sum+=d;
        if( sum > L3)
        {
            //купили билет
            price+=getPriceByDist(sum_prev);
            sum = d;
        }
        sum_prev = sum;
        n++;
    }
    //купить последний билет
    price+=getPriceByDist(sum_prev);
    return price;

}
