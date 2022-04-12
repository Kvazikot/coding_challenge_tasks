// http://acm.timus.ru/problem.aspx?space=1&num=1093
#include <QDebug>
#include "darts1093.h"
#include "vector3d.h"

CVector3 line(CVector3 V, CVector3 X0, double t)
{
    CVector3 R;
    R = X0 + V * t;
    return R;
}

CVector3 traj(CVector3 S, CVector3 V, double t)
{
    CVector3 M;
    const float g = 10;
    M.x = S.x + V.x*t;
    M.y = S.y + V.y*t;
    M.z = S.z + V.z*t -(g/2.)*t*t;
    return M;
}

CVector3 intersect_line_plane(CVector3 N, CVector3 X, CVector3 Y, CVector3 A, float& to)
{
    CVector3 V = A - X;

    // расстояние до плоскости по нормали
    float d = N | V;
    CVector3 W = Y - X;

    // приближение к плоскости по нормали при прохождении отрезка
    float e = N | W;

    // точка пересечения прямой с плоскостью
    CVector3 O;
    if( e!=0 )
      O = X + W * d/e;          // одна точка
    to = d/e;
    return O;
}


int sign(float x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

Darts1093::Darts1093(float Cx,float Cy,float Cz,float Nx,float Ny,
          float Nz,float R,float Sx,float Sy,float Sz,
          float Vx,float Vy,float Vz ):
    Cx(Cx),Cy(Cy),Cz(Cz),Nx(Nx),Ny(Ny),Nz(Nz),R(R),Sx(Sx),Sy(Sy),Sz(Sz),
    Vx(Vx),Vy(Vy),Vz(Vz)
{

    CVector3 N(Nx,Ny,Nz);
    CVector3 A(Cx,Cy,Cz);
    CVector3 V(Vx,Vy,Vz);

    // первая точка прямой
    CVector3 S(Sx,Sy,Sz);

    float t = 0.0001, t0 = t;
    float d=0, d0=0;

    // уходим за плоскость дартса
    CVector3 X,Y;
    X = traj(S,V,t);
    CVector3 B = A - X;
    // расстояние до плоскости по нормали
    d = N | B; d0 = d;
    while( sign(d) == sign(d0) )
    {
        d0 = d; t0 = t;
        X = traj(S,V,t);
        B = A - X;
        // расстояние до плоскости по нормали
        d = N | B;
        t = t * 2;
        qDebug() << X.x << "," << X.y << "," << X.z;
        qDebug() << "t=" << t;
    }

    // найдем t0 точки пересечения прямой и плоскости дартса
    X = traj(S,V,t0);
    Y = traj(S,V,t);
    Y = intersect_line_plane(N,X,Y,A,t);
    qDebug() << "tp=" << t;
    //Y = traj(X,V,t0+t);

    // проверим попадает ли Y в круг
    CVector3 M = A - Y;
    M.findMagnitude();
    qDebug() << M.mag;
    if( M.mag > R )
        qDebug() << "MISS";
    else
        qDebug() << "HIT";


}
