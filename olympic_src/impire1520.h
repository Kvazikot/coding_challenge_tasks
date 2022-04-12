#ifndef IMPIRE1520_H
#define IMPIRE1520_H

#include <QPainter>
#include <QPointF>
#include "mainwindow.h"

struct Interval2
{
    Interval2()
    {
        ymin = 0; ymax = 0;
    }
    Interval2(double ymin, double ymax)
        :ymin(ymin), ymax(ymax)
    {
    }

    bool contains(Interval2 i2)
    {
        if( (i2.ymax <= ymax) && (i2.ymin >= ymin) )
        {
            return true;
        }
        return false;
    }

    Interval2 isIntersects(Interval2 i2)
    {
        Interval2 intersection;
        // содержится
        if( (i2.ymax > ymax) && (i2.ymin < ymin) )
        {
            intersection.ymax = i2.ymax;
            intersection.ymin = i2.ymin;
            return intersection;
        }
        if( (i2.ymax < ymax) && (i2.ymin > ymin) )
        {
            intersection.ymax = ymax;
            intersection.ymin = ymin;
            return intersection;
        }

        //пересечение
        if( (i2.ymax > ymin) && (ymin > i2.ymin) )
        {
            intersection.ymax = ymax;
            intersection.ymin = i2.ymin;
        }
        if( (i2.ymin < ymax) && (i2.ymin > ymin) )
        {
            intersection.ymax = i2.ymax;
            intersection.ymin = ymin;
        }

        return intersection;
    }

    bool isNil()
    {
        return (ymin == 0) && (ymax == 0) ;
    }


    double ymin, ymax;

};

class Impire1520
{
public:
    std::vector<QPointF> blue_points;
    Impire1520(MainWindow* mw);
    bool point_inside(double al, QPointF c, double r, double R);
    bool coverCircles(double r, std::vector<QPointF> points, int R);
    double divide(double t0, double t, int deep,
                             std::vector<QPointF> points, double R, int N);

};

#endif // IMPIRE1520_H
