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

int sign(float x)
{
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}


float func(float t, CVector3 S, CVector3 V, CVector3  A)
{
    CVector3 X = traj(S,V,t);
    CVector3 B = A - X;
    B.findMagnitude();
    // расстояние до плоскости по нормали
    return B.mag;
}

float divide(float t0, float t, CVector3 S, CVector3 V, CVector3  A, float R, int deep)
{
    float t1,t2, tmid;
    t1 = t0 + (t-t0)/4.;
    t2 = t - (t-t0)/4.;
    tmid = t0 + (t-t0)/2.;
    deep = deep + 1;
    if( deep > 100000 )
        return tmid;
     if( func(tmid,S,V,A) < R )
    {
        qDebug() << "HIT";
        return tmid;
    }
    if( func(t1, S, V, A) <  func(t2, S, V, A))
      return divide(t0, tmid, S, V, A, R, deep);
    else
      return divide(tmid, t, S, V, A, R, deep);

    return tmid;
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
    }

    t = divide(t0/2, t, S, V, A, R, 1);
    if( func(t,S,V,A) > R )
        qDebug() << "MISS";




}
