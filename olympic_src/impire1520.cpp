// http://acm.timus.ru/problem.aspx?space=1&num=1520&locale=ru
#include "impire1520.h"
#include <QStringList>
#include <map>
#include <QPointF>
#include <QPainter>
#include <QtGlobal>
#include <QElapsedTimer>
#include <vector>
#include <QDebug>
#define _USE_MATH_DEFINES
#include <math.h>


void join_intervals(std::vector<Interval2>& intervals, std::vector<Interval2>& intervals_joined)
{
    std::map<int,int> intersect;
    std::map<std::pair<int,int>,int> pairs;
    std::map<std::pair<double,double>,int> dublicates;
    for(int i=0; i < intervals.size(); i++)
    for(int j=0; j < intervals.size(); j++)
    {
        if(pairs.find(std::make_pair(i,j))==pairs.end())
        {
            pairs[std::make_pair(i,j)] = 1;
            pairs[std::make_pair(j,i)] = 1;
            Interval2 interval = intervals[i].isIntersects(intervals[j]);
            if( !interval.isNil() )
            {
                intersect[i] = 1;
                intersect[j] = 1;
                if(dublicates.find(std::make_pair(interval.ymax,interval.ymin))==dublicates.end())
                {
                    intervals_joined.push_back(interval);
                    dublicates[std::make_pair(interval.ymax,interval.ymin)] = 1;
                }
            }
        }

    }
    //внести непересекающиеся
    for(int i=0; i < intervals.size(); i++)
        if(intersect.find(i)==intersect.end())
            intervals_joined.push_back( intervals[i] );
}

double Impire1520::divide(double t0, double t, int deep,
                         std::vector<QPointF> points, double R, int N)
{
    double t1,t2, tmid;
    t1 = t0 + (t-t0)/4.;
    t2 = t - (t-t0)/4.;
    tmid = t0 + (t-t0)/2.;
    deep = deep + 1;

    if( deep > 50 )
        return tmid;

    if( (t - t0) < 0.0000001 )
        return tmid;

    //double sum = integral(points,R,tmid,N);
    bool b = coverCircles(tmid, points, R);

    if( b == true)
      return divide(t0, tmid, deep, points,R,N);
    else
      return divide(tmid, t, deep, points,R,N);

    return tmid;
}

#define sq(a) a*a

double rasst(QPointF p1, QPointF p2)
{
     double _t1 = (double)sqrt( (double) ( (p1.x() - p2.x())*(p1.x() - p2.x())
                                           +  (p1.y() - p2.y())*(p1.y() - p2.y()) ))  ;
     return _t1;
}


bool containCircles(QPointF c0, QPointF c1, double r0, double r1)
{
    double d = rasst(c0, c1);
    if(d < fabs(r0 - r1)) return true;
    return false;
}

int IntersectCircles(QPointF c0, QPointF c1, double r0, double r1,
                      QPointF& p31, QPointF& p32)
{
    double d = rasst(c0, c1);
    if(d > r0 + r1) return 0;
    if(d < fabs(r0 - r1))
        return 1;

    //по теореме косинусов
    double cos_a = (r0*r0 -(r1*r1) + d*d) / (2*r0*d);
    double sin_a = sqrt(1 - cos_a*cos_a);

    double a = (r0*r0 - r1*r1 + d*d)/(2*d);

    // находим высоту
    double h = r0 * sin_a;


    QPointF P2;
    P2 = c0 + a/d*(c1 - c0);

    p31.setX(P2.x() + h * ( c1.y() - c0.y() ) / d);
    p31.setY(P2.y() - h * ( c1.x() - c0.x() ) / d);

    p32.setX(P2.x() - h * ( c1.y() - c0.y() ) / d);
    p32.setY(P2.y() + h * ( c1.x() - c0.x() ) / d);

    //p31 = P2;
    //p32 = P2 - h * ( c1 - c0 ) / d;
    return 2;

}

double get_angle(double x, double y)
{

    if( x > 0 && y >=0 )
        return atan(y/x);
    if( x > 0 && y < 0 )
        return atan(y/x) + 2 * M_PI;
    if( x < 0)
        return atan(y/x) + M_PI;
    if( x == 0 && y > 0)
        return M_PI / 2;
    if( x == 0 && y < 0)
        return 3 * M_PI / 2;
    return 0;

    //return atan2(y,x);
}

bool Impire1520::point_inside(double al, QPointF c, double r, double R)
{
    double y = c.y() + sin((double)al)*r;
    double x = c.x() + cos((double)al)*r;
    //blue_points.push_back(QPointF(x,y));

    if((x*x + y*y) <=R*R)
        return true;
    else
        return false;

}

bool Impire1520::coverCircles(double r, std::vector<QPointF> points, int R)
{
    std::vector<Interval2> intervals;


    //пересечение
    for(int i=0; i < points.size(); i++)
    {
        QPointF p = points[i];
        QPointF p31,p32;
        int ret = IntersectCircles(QPointF(0,0),p,R,r,p31,p32);
        //if( ret == 1) return true;
        double a1 = get_angle(p31.x(), p31.y());
        double a2 = get_angle(p32.x(), p32.y());
        if( a1 > a2 ) std::swap(a1,a2);
        if( (a2 - a1) > M_PI)
        {
            intervals.push_back(Interval2(0,a1));
            intervals.push_back(Interval2(a2,2*M_PI));
/*
            double a3 = get_angle(p31.x()-p.x(), p31.y()-p.y());
            double a4 = get_angle(p32.x()-p.x(), p32.y()-p.y());
            if( a3 > a4 ) std::swap(a3,a4);

            if( point_inside(a3 - fabs(a2-a1)/2,p,r,R) )
            {
                //qDebug() << "1";
            }

            if( point_inside(a3 + fabs(a2-a1)/2,p,r,R) )
            {
                //qDebug() << "1";
            }

*/
        }
           else
            {
                intervals.push_back(Interval2(a1,a2));

            }
    }
    std::vector<Interval2> intervals_joined;
    for(int i=0; i < points.size(); i++)
    {
        join_intervals(intervals, intervals_joined);
        intervals = intervals_joined;
        intervals_joined.clear();
    }

    //if( intervals.size() == 1 )
    for(int i=0; i < intervals.size(); i++)
    {
        if( (intervals[i].ymax == 2 * M_PI) && (intervals[i].ymin == 0))
            return true;
    }
     return false;

}

Impire1520::Impire1520(MainWindow* mw)
{
    QStringList input;
    input.append("4 4");
    input.append("0 2");
    input.append("2 0");
    input.append("-2 0");
    input.append("0 -2");
    //input.append("-3 0");
    std::vector<QPointF> points;
    QStringList parts = input[0].split(" ");
    int N = parts[0].toInt();
    int R = parts[1].toInt();
    for(int i=0; i < N; i++)
    {
        QStringList parts = input[i+1].split(" ");
        points.push_back(QPointF( (float) parts[0].toInt() ,
                                  (float) parts[1].toInt()));
    }
    qDebug() << "done!";

    if( N == 1 )
    {
        qDebug() << R;
        return;
    }



    bool b1 = coverCircles(2.1, points, R);
    qDebug() << b1;
    //bool b2 = coverCircles(4, points, R);
    //qDebug() << b2;

    QElapsedTimer timer;
    timer.start();
    double r = divide(0,2*R,0,points,R,N);
    //double r = 2;

    qDebug() << r;
    qDebug() << "timer " << timer.elapsed();


    //создать изображение пересекающихся кругов
    int RES = 800;
    QImage image(RES+10, RES+10, QImage::Format_ARGB32);
    QPainter painter(&image);
    image.fill(Qt::white);
    painter.setPen(Qt::red);
    double k = RES / 20;
    QPoint c(RES/2, RES/2);
    painter.drawEllipse(c, (int)(4*k), (int)(4*k));
    painter.setPen(Qt::black);
    for(int i=0; i < N; i++)
    {
        QPointF p = points[i];
        painter.drawEllipse( QPoint(p.x()*k  + RES/2, p.y()*k + RES/2), int(r*k), int(r*k));
    }
    for(int i=0; i < blue_points.size(); i++)
    {
        QPointF p = blue_points[i];
        painter.setPen(Qt::blue);
        painter.drawEllipse( QPoint(p.x()*k  + RES/2, p.y()*k + RES/2), 10, 10);
    }

    mw->setImage(image);

}

