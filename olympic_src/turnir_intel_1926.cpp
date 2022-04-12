#include "turnir_intel_1926.h"
#include <QDebug>
#include <QStringList>
#include <limits>
//http://acm.timus.ru/problem.aspx?space=1&num=1926

Turnir_intel_1926::Turnir_intel_1926()
{
    QStringList input;
    std::numeric_limits<int> l;
    qDebug() << "int max = " << l.max();
    BigInt i,j,result;
    i.Init("100000000");
    j.Init("10");
    result = i * j;
    BigInt b = i.pow(10,10);
    BigInt min = BigInt("212499999");
    BigInt max = BigInt("212499999");
    QString bin = max.toBin();
    bin = bin.mid(1,bin.length()-1);
    qDebug() << bin;
    qDebug() << max.fromBin2(bin).num;
    b = (max)/2;
    //qDebug() << "b=" << b.num;
    return;
    input.append("4100056789890004321");
    input.append("6");
    input.append("5 9897654321");
    input.append("0 1");
    input.append("0 7");
    input.append("0 10");
    input.append("1 2 9");
    input.append("0 6");

    ParseInput(input);

}

void Turnir_intel_1926::ParseInput(QStringList list)
{
    n = BigInt(list[0]);
    int m = list[1].toInt();
    for(int i=0; i<m; i++)
    {
        QStringList parts = list[i+2].split(" ");
        if(parts[0].toInt() == 0)
        {
            int r = getRemain(parts[1].toInt());
            qDebug() << r;
        }
        else if(parts[0].toInt() == 1)
        {
            changeDigit(parts[1].toInt(), parts[2].toInt());
            //qDebug() << n.num;
        }
        else if(parts[0].toInt() == 2)
        {
           BigInt C = n + BigInt(parts[1]);
           qDebug() << C.num;
        }
        else if(parts[0].toInt() == 3)
        {
           BigInt C = n - BigInt(parts[1]);
           qDebug() << C.num;
        }
        else if(parts[0].toInt() == 4)
        {
           BigInt C = n * BigInt(parts[1]);
           qDebug() << C.num;
        }
        else if(parts[0].toInt() == 5)
        {
           BigInt C = n / BigInt(parts[1]);
           qDebug() << C.num;
        }
    }
}

int Turnir_intel_1926::getRemain(int divider)
{
      return n.getRemainder(divider);
}

int Turnir_intel_1926::changeDigit(int k, int b)
{
    n.num.replace(k,1,QString::number(b));
    n.Init(n.num);
}

