#ifndef LINEPAINTING1019_H
#define LINEPAINTING1019_H

#include <QString>
#include <vector>

struct Interval
{
    Interval(int a, int b, char color)
        :a(a),b(b),color(color)
    {
    }

    int Len(){ return b - a; }
    bool isLeaf() { return children.size() == 0; }
    bool contains(Interval* I)
    {
        return (a < I->a) && (b > I->b);
    }
    bool intersects(Interval* I)
    {
        return ( I->a <= b) || ( I->b >= a);
    }
    void insert(Interval* newInterval);
    void joinRecursive();
    void getMaxRecursive(Interval* I);
    void join(Interval* I)
    {
        a = qMin(a, I->a);
        b = qMax(b, I->b);
        for(auto it=I->children.begin(); it!=I->children.end(); it++)
        {
            children.push_back(*it);
        }
    }

    int a,b;
    char color;
    std::vector<Interval*> children;
};

class LinePainting1019
{
public:
    std::vector<Interval*> intervals;
    LinePainting1019(QString input);
};

#endif // LINEPAINTING1019_H
