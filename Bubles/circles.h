#ifndef CIRCLES_H
#define CIRCLES_H

#include <math.h>
#include <algorithm>
#include <vector>

struct Circle
{
    float r;
    float   xc;
    float   yc;
    Circle(float r, float x, float y):xc(x),yc(y),r(r)
    {}
    bool intersect(Circle B)
    {
        float distance = sqrt((xc-B.xc)*(xc-B.xc) + (yc-B.yc)*(yc-B.yc));
        return (distance > (r+B.r)) ? false : true;
    }
};

struct Circles
{
    std::vector<Circle> circles;

    Circles(){}
    void add(Circle c) { circles.push_back(c); }
    bool add_not_intersect(Circle c)
    {
        bool bIntersects=false;
        for(auto it=circles.begin(); it!=circles.end(); it++)
        {
            if( (*it).intersect(c))
            {
                    bIntersects=true;
                    break;
            }
        }
        if(!bIntersects) add(c);
        return !bIntersects;
    }
    void sortByRadius()
    {
        std::sort(circles.begin(), circles.end(), [&](Circle& A, Circle& B)
                                            {
                                                return A.r > B.r;
                                            });
    }

};
#endif // CIRCLES_H
