#include "vavilon_ribka1836.h"
#include <QDebug>
#include "vector3d.h"
//http://acm.timus.ru/problem.aspx?space=1&num=1836

double getZfromPlane(CVector3 N, double x, double y, CVector3 Origin)
{
    return (-N.x*(x-Origin.x) - N.y * (y-Origin.y))/N.z + Origin.z;
    //return x/10+y/10+2;
}

bool inPlane(CVector3 A, CVector3 B, CVector3 C, CVector3 D)
{
    // normal vector
    CVector3 N;
    N = (D-A)^(B-A);
    double z = getZfromPlane(N, C.x, C.y, A);
    return z == C.z;
}

vavilon_ribka1836::vavilon_ribka1836()
{
    CVector3 A(0,0,2);
    CVector3 B(10,0,3);
    CVector3 C(10,10,4);
    CVector3 D(0,10,3);
    int max_iters = 20000;

    if(inPlane(A,B,C,D)==false)
    {
       qDebug() << "error";
       return;
    }

    // normal vector
    CVector3 N;
    N = (D-A)^(B-A);


    double V=0;

    // brute force method
   // qDebug() << (10/0.001)*(10/0.001);
/*
    double DX=0.001,DY=0.001;
    for(double X=DX; X < 10; X+=DX)
    {

        for(double Y=DY; Y < 10; Y+=DY)
        {

            C.z = getZfromPlane(N, X, Y, B);

            V+=DX * DY * C.z;
        }
    }
*/
    //monte carlo method
    int iters=0;
    int n_under_plane=0;
    double X,Y,Z;
    while(iters < max_iters)
    {
        X = 10 * (double)rand()/RAND_MAX;
        Y = 10 * (double)rand()/RAND_MAX;
        Z = 10 * (double)rand()/RAND_MAX;

        double z = getZfromPlane(N, X, Y, B);
        if(Z < z)
            n_under_plane++;

        iters++;
    }
    V = ceil((double)(10*10*10) * (double)n_under_plane / max_iters);

    qDebug() << "V=" << V;

}
