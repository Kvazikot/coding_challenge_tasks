#include <QStringList>
#include <QDebug>
#include "linepainting1019.h"

LinePainting1019::LinePainting1019(QString input)
{
    QStringList lines = input.split(",");
    int Nintervals = lines[0].toInt();
    for(int i=1; i < lines.size(); i++)
    {
        QStringList parts = lines[i].split(" ");
        char col = 0;
        if(parts[2] == "w")
            col = 1;
        bool ok1,ok2;
        Interval* I = new Interval(parts[0].toInt(&ok1),
                                   parts[1].toInt(&ok2),
                                   col);
        if(ok1 && ok2)
          intervals.push_back(I);

    }

    // 0 - сортировка по длинне
    std::sort(intervals.begin(), intervals.end(),
              []( Interval*  a,  Interval*  b) -> bool
    {
              return a->Len() > b->Len();
    });

    //1- создание дерева
    Interval* root = intervals[0];
    for(int i=1; i < intervals.size(); i++)
        root->insert(intervals[i]);

    //2 - обьединить пересекающиеся
    root->joinRecursive();

    //3 - выбрать наибольший белый интервал
    root->getMaxRecursive(root);

    qDebug() << root->children[0]->a << " " << root->children[0]->b;
}


void Interval::getMaxRecursive(Interval* I)
{
    std::vector<Interval*> whites;
    if(I->color == 1)
    {
        int a = I->a;
        for(auto it=I->children.begin(); it!=I->children.end(); it++)
        {
            Interval* I2 = new Interval(a, (*it)->a, 1);
            whites.push_back(I2);
            a = (*it)->b;
        }
        Interval* I2 = new Interval(a, I->b, 1);
        whites.push_back(I2);
    }
    if(whites.size())
    {
        std::sort(whites.begin(), whites.end(),
                  []( Interval*  a,  Interval*  b) -> bool
        {
                  return a->Len() > b->Len();
        });
        I->a = whites[0]->a;
        I->b = whites[0]->b;
    }
    for(auto it=I->children.begin(); it!=I->children.end(); it++)
      getMaxRecursive(*it);
}

void Interval::joinRecursive()
{
    std::vector<std::pair<Interval*, Interval*> > to_join;
    for(auto it=children.begin(); it!=children.end(); it++)
        for(auto it2=children.begin(); it2!=children.end(); it2++)
        {
            if( (*it)!=(*it2) )
              if( (*it)->intersects(*it2)   )
              {
                  auto t = std::find(to_join.begin(), to_join.end(), std::make_pair(*it2,*it));
                  if(t==to_join.end())
                    to_join.push_back( std::make_pair(*it, *it2) );
              }

        }

    // join
    std::vector<std::pair<Interval*, Interval*> >::iterator it;
    for(it = to_join.begin(); it!=to_join.end(); it++)
        (*it).first->join((*it).second);

    //выкинуть вторые из детей
    for(it = to_join.begin(); it!=to_join.end(); it++)
        children.erase(std::find(children.begin(), children.end(),(*it).second));

    for(auto it=children.begin(); it!=children.end(); it++)
        (*it)->joinRecursive();

}

void Interval::insert(Interval* newInterval)
{
    if( isLeaf() )
    {
        children.push_back( newInterval );
    }
    else
    {
        bool inserted = false;
        for(auto it=children.begin(); it!=children.end(); it++)
        {
            if( (*it)->contains(newInterval) )
            {
                (*it)->insert(newInterval);
                inserted = true;
            }
        }
        if( !inserted )
          children.push_back( newInterval );
    }
    std::sort(children.begin(), children.end(),
              []( Interval*  a,  Interval*  b) -> bool
    {
              return a->Len() > b->Len();
    });
}
