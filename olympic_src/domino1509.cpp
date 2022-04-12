#include <QTime>
#include <QImage>
#include <QPainter>
#include <QDebug>
#include <random>
#include <math.h>
#include "domino1509.h"

QImage drawDomino(Knuckle& domino)
{

    int RES = 800;
    QImage image(RES+10, RES+10, QImage::Format_ARGB32);
    QPainter painter(&image);
    image.fill(Qt::white);
    double k = RES / 200;
    const int r = 2;
    painter.setPen(Qt::black);
    for(int i=0; i < domino.points.size(); i++)
    {
        QPointF p = domino.points[i];
        painter.drawEllipse( QPoint(p.x()*k  + RES/2, p.y()*k + RES/2), int(r*k), int(r*k));
    }
    return image;
}

Knuckle::Knuckle(int n1, int n2)
    : n1(n1),n2(n2)
{
    angle = 0;
    GeneratePoints(n1, true);
    GeneratePoints(n2, false);
}

Knuckle::Knuckle(int n1, int n2, float a)
    : n1(n1),n2(n2)
{
    setAngle(a);
    GeneratePoints(n1, true);
    GeneratePoints(n2, false);
}

Knuckle::Knuckle(int n_points)
{
    srand(QTime::currentTime().second());
    angle = rand()%180;
    switch(n_points)
    {
        case 1:
            GeneratePoints(1, true);
        break;
        case 2:
        {
           if( (rand()%100) > 50 )
           {
                GeneratePoints(1, true);
                GeneratePoints(1, false);
           }
           else
           {
               GeneratePoints(2, true);
               GeneratePoints(0, false);
           }
         }
        break;
        case 3:
        {
            if( (rand()%100) > 50 )
            {
                 GeneratePoints(1, true);
                 GeneratePoints(2, false);
            }
            else
            {
                GeneratePoints(0, true);
                GeneratePoints(3, false);
            }
        }
        case 4:
        {
           int p = rand()%100;
           if( p < 33)
           {
               GeneratePoints(2,true);
               GeneratePoints(2,false);
           }
           else if( p > 66)
           {
               GeneratePoints(4,true);
               GeneratePoints(0,false);
           }
           else if( p < 66)
           {
               GeneratePoints(3,true);
               GeneratePoints(1,false);
           }


        }
        break;
    case 5:
    {
       int p = rand()%100;
       if( p < 33)
       {
           GeneratePoints(4,true);
           GeneratePoints(1,false);
       }
       else if( p > 66)
       {
           GeneratePoints(5,true);
           GeneratePoints(0,false);
       }
       else if( p < 66)
       {
           GeneratePoints(3,true);
           GeneratePoints(2,false);
       }
    }
    break;
    case 6:
    {
       int p = rand()%100;
       if( p < 33)
       {
           GeneratePoints(6,true);
           GeneratePoints(0,false);
       }
       else if( p > 66)
       {
           GeneratePoints(3,true);
           GeneratePoints(3,false);
       }
       else if( p < 66)
       {
           GeneratePoints(4,true);
           GeneratePoints(2,false);
       }
    }
    break;
    case 7:
    {
       int p = rand()%100;
       if( p < 33)
       {
           GeneratePoints(4,true);
           GeneratePoints(3,false);
       }
       else if( p > 66)
       {
           GeneratePoints(5,true);
           GeneratePoints(2,false);
       }
       else if( p < 66)
       {
           GeneratePoints(6,true);
           GeneratePoints(1,false);
       }
    }
    break;
    case 8:
    {
       int p = rand()%100;
       if( p < 33)
       {
           GeneratePoints(4,true);
           GeneratePoints(4,false);
       }
       else if( p > 66)
       {
           GeneratePoints(6,true);
           GeneratePoints(2,false);
       }
       else if( p < 66)
       {
           GeneratePoints(5,true);
           GeneratePoints(3,false);
       }
    }
    break;
    case 9:
    {
       if( (rand()%100) > 50 )
       {
            GeneratePoints(5, true);
            GeneratePoints(4, false);
       }
       else
       {
           GeneratePoints(3, true);
           GeneratePoints(6, false);
       }
     }
    break;
    case 10:
    {
       if( (rand()%100) > 50 )
       {
            GeneratePoints(4, true);
            GeneratePoints(6, false);
       }
       else
       {
           GeneratePoints(5, true);
           GeneratePoints(5, false);
       }
    }
    break;

    case 11:
        GeneratePoints(5, true);
        GeneratePoints(6, false);
    break;
    case 12:
        GeneratePoints(6, true);
        GeneratePoints(6, false);
    break;
    }

}

void Knuckle::GeneratePoints(int n, bool first)
{
    const int size = 10;
    QRectF rect(QPointF(0,0), QPointF(size,size));
    QPointF p1(0,0);
    QPointF p2(0,size);
    QPointF p3(size,0);
    QPointF p4(size,size);

    // translate 20


    QTransform t;
    t.rotate(angle);
    if(!first)
        t.translate(size*1.8, 0);
    p1 = p1 * t;
    p2 = p2 * t;
    p3 = p3 * t;
    p4 = p4 * t;
    rect = QRectF(p1,p4);



    switch(n)
    {
        case 1:
           points.push_back(rect.center());
        break;
        case 2:
           points.push_back(p2);
           points.push_back(p3);
        break;
        case 3:
          points.push_back(p2);
          points.push_back(p2 + (p3 - p2)/2);
          points.push_back(p3);
        break;
        case 4:
          points.push_back(p1);
          points.push_back(p2);
          points.push_back(p3);
          points.push_back(p4);
        break;
        case 5:
          points.push_back(p1);
          points.push_back(p2);
          points.push_back(p3);
          points.push_back(p4);
          points.push_back(p2 + (p3 - p2)/2);
        break;
        case 6:
          points.push_back(p1);
          points.push_back(p2);
          points.push_back(p3);
          points.push_back(p4);
          points.push_back(p1 + (p3 - p1)/2);
          points.push_back(p4 + (p2 - p4)/2);
        break;

    };


}

double rasst2(QPointF p1, QPointF p2)
{
     double _t1 = (double)( (double) ( (p1.x() - p2.x())*(p1.x() - p2.x())
                                           +  (p1.y() - p2.y())*(p1.y() - p2.y()) ))  ;
     return _t1;
}

bool checkSquare(std::vector<QPointF>& points)
{
    double r1 = rasst2(points[0],points[1]);
    double r2 = rasst2(points[1],points[2]);
    double r3 = rasst2(points[2],points[3]);
    double r4 = rasst2(points[3],points[0]);
    double d1 = fabs(r1 - r2);
    double d2 = fabs(r2 - r3);
    double d3 = fabs(r3 - r4);
    double d4 = fabs(r1 - r4);
    const double EPS = 10e-6;
    return (d1 < EPS) && (d2 < EPS) && (d3 < EPS) && (d4 < EPS);
}

bool isMidPoint(QPointF p1, QPointF p2, QPointF p3)
{
    const double EPS = 10e-6;
    QPointF c1 = p1 + (p2 - p1) / 2;
    QPointF c2 = p1 + (p1 - p2) / 2;
    QPointF c3 = p2 + (p2 - p1) / 2;
    QPointF c4 = p2 + (p1 - p2) / 2;
    if( rasst2(p3,c1) < EPS )
        return true;
    if( rasst2(p3,c2) < EPS )
        return true;
    if( rasst2(p3,c3) < EPS )
        return true;
    if( rasst2(p3,c4) < EPS )
        return true;
    return false;

}

bool checkMidPoint(std::vector<QPointF>& points)
{
    const double EPS = 10e-6;
    QPointF c = points[0] + (points[2] - points[0]) / 2;
    if( rasst2(c, points[1])  < EPS )
        return true;
    return false;
}

int checkFiveSix(std::vector<QPointF>& points, std::vector<QPointF>& other_points)
{
    const double EPS = 10e-6;
    std::vector<std::pair<int,int> > pairs;
    std::vector<QPointF> mid_points;
    pairs.push_back( std::make_pair(0,1) );
    pairs.push_back( std::make_pair(1,3) );
    pairs.push_back( std::make_pair(2,3) );
    pairs.push_back( std::make_pair(0,2) );
    pairs.push_back( std::make_pair(1,2) );
    pairs.push_back( std::make_pair(0,3) );
    for(auto it2=pairs.begin(); it2!=pairs.end(); it2++)
    {
        for(auto it=other_points.begin(); it!=other_points.end(); it++)
        {
            if( isMidPoint( points[(*it2).first],
                            points[(*it2).second],
                            *it) )
            {
                mid_points.push_back(*it);
            }
        }
    }
    if( mid_points.size()==2 )
    {
        if(mid_points[0]!=mid_points[1])
           return 6;
         else
            return 5;
    }

    return 0;
}

int findSquare(std::vector<QPointF>& points)
{
    int iter = 2000;

    if( points.size() < 4 )
        return -1;

    std::random_device rd;
    std::mt19937 g(rd());

    while(iter > 0)
    {
        std::vector<QPointF> points2 = points;
        std::shuffle(points2.begin(), points2.end(), g);
        std::vector<QPointF> removed_points;
        if( points2.size() > 4 )
          std::copy(points2.begin()+4,points2.end(),back_inserter(removed_points));
        /*
        while((points2.size()!=4))
        {
            int n = rand()%(points2.size());
            removed_points.push_back(points2[n]);
            auto it = points2.erase(points2.begin() + n);
            //std::remove(points2.end(),it);
        }
        */
        if( checkSquare(points2) )
        {
            //qDebug() << "iters " << 2000 - iter;
            int res = checkFiveSix(points2, removed_points);
            if( res )
                return res;
            else
               return 4;
        }
        iter--;
    }
    return -1;

}

bool findMidPoint(std::vector<QPointF>& points)
{
    int iter = 2000;

    if( points.size() < 3 )
        return -1;

    std::random_device rd;
    std::mt19937 g(rd());

    while(iter > 0)
    {
        std::vector<QPointF> points2 = points;
        std::shuffle(points2.begin(), points2.end(), g);
        std::vector<QPointF> removed_points;
        if( points2.size() > 3 )
          std::copy(points2.begin()+3,points2.end(),back_inserter(removed_points));

        if( checkMidPoint(points2) )
        {
            return true;
        }
        iter--;
    }
    return false;

}

void recognizeDomino(std::vector<QPointF>& points)
{
    int square_ret = findSquare(points);
    bool isMidPoint = findMidPoint(points);
    switch(points.size())
    {
         case 1:
             qDebug("0 1");
         break;
         case 11:
            qDebug("5 6");
         break;
         case 12:
            qDebug("6 6");
         break;
         case 2:
            qDebug("1 1");
            qDebug("2 0");
         break;
         case 3:
           if( findMidPoint(points) )
               qDebug("3 0");
           else
               qDebug("1 2");
          break;
        case 4:
           if( findSquare(points) == 4 )
           {
               qDebug("4 0");
               break;
           }
           if( findMidPoint(points) )
           {
               qDebug("3 1");
               break;
           }
           qDebug("2 2");
        break;
        case 5:
          if( square_ret == 4 )
          {
              qDebug("4 1");
              break;
          }
          if( square_ret == 5 )
          {
              qDebug("5 0");
              break;
          }
          qDebug("3 2");
        break;
        case 6:
            if( square_ret == 6 )
            {
                qDebug("6 0");
                break;
            }
            if( square_ret == 4 )
            {
                qDebug("4 2");
                break;
            }
            qDebug("3 3");
        break;
        case 7:
            if( square_ret == 4 )
            {
                qDebug("4 3");
                break;
            }
            if( square_ret == 5 )
            {
                qDebug("5 2");
                break;
            }
            qDebug("6 1");
        break;
        case 8:
            if( square_ret == 4 )
            {
                qDebug("4 4");
                break;
            }
            if( square_ret == 5 )
            {
                qDebug("5 3");
                break;
            }
            qDebug("6 2");
        break;
        case 9:
            if( square_ret == 6 )
            {
                qDebug("3 6");
                break;
            }
            qDebug("5 4");
        break;
        case 10:
            if( square_ret == 5 )
            {
                qDebug("5 5");
                break;
            }
            qDebug("4 6");
        break;

    }

}

void Domino1509::slotKeyPress(int key)
{
    Knuckle domino9(rand()%11+1);
    qDebug() << "-----------------------";
    recognizeDomino(domino9.points);
    QImage image = drawDomino(domino9);
    mw->setImage(image);
}

Domino1509::Domino1509(MainWindow* mw)
{
    this->mw = mw;
    Knuckle domino(3,2,rand()%180);
//    qDebug() << "domino(5,5,30) findSquare " << findSquare(domino.points);
//    Knuckle domino2(5,1,rand()%180);
//    qDebug() << "domino(5,0,30) findSquare " << findSquare(domino2.points);
//    Knuckle domino3(6,1,rand()%180);
//    qDebug() << "domino(6,0,30) findSquare " << findSquare(domino3.points);
//    Knuckle domino4(4,1,rand()%180);
//    qDebug() << "domino(4,0,30) findSquare " << findSquare(domino4.points);
//    Knuckle domino5(5,2,rand()%180);
//    qDebug() << "domino(5,2,30) findSquare " << findSquare(domino5.points);
//    Knuckle domino6(6,3,rand()%180);
//    qDebug() << "domino(6,3,30) findSquare " << findSquare(domino6.points);
//    Knuckle domino7(3,3,rand()%180);
//    qDebug() << "domino(3,3,30) findSquare " << findSquare(domino7.points);
//    Knuckle domino8(5,4,rand()%180);
//    qDebug() << "domino(5,4,30) findSquare " << findSquare(domino8.points);

    //qDebug() << "domino(6,0,30) findMidPoint " << findMidPoint(domino.points);

    connect(mw, SIGNAL(on_keypress(int)), this, SLOT(slotKeyPress(int)));
    Knuckle domino9(7);
    recognizeDomino(domino.points);
    QImage image = drawDomino(domino);
    mw->setImage(image);

}
