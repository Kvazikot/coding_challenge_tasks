#include <math.h>
#include <QPainter>
#include <QStringList>
#include <QPointF>
#include <QDebug>
#include "rope1020.h"
#include <QVector2D>

#define sq(a) ((a) * (a))

RopeBase::RopeBase(QString input)
{
    QStringList lines = input.split(",");
    QStringList parts = lines[0].split(" ");
    N = parts[0].toInt();
    R = parts[1].toFloat();
    for(int i=1; i < lines.size(); i++)
    {
        QStringList parts = lines[i].split(" ");
        points.push_back(QPointF(parts[0].toFloat(), parts[1].toFloat()));
    }
    //зациклить
    points.insert(points.begin(),*(points.end()-1));
    points.push_back(*(points.begin()+1));

}

float RopeBase::rasst(QPointF p1, QPointF p2)
{
     float _t1 = (float)sqrt( (double) ( sq(p1.x() - p2.x())  +  sq(p1.y() - p2.y() )))  ;
     return _t1;
}


float RopeBase::calcArcLength(QPointF A, QPointF C, QPointF B, float R)
{
    QVector2D v1 = QVector2D(A) - QVector2D(C);
    QVector2D v2 = QVector2D(B) - QVector2D(C);
    float dot = fabs(v1.dotProduct(v1,v2));
    float angle = acos(sqrt(dot/(v1.length()*v2.length())));
    return R * angle;
}

float RopeBase::calcRope(float R, std::vector<QPointF> points, int N)
{
    float length = 0;
    for(int i=1; i <= N; i++)
    {
        length+=calcArcLength(points[i-1], points[i], points[i+1], R);
        length+=rasst(points[i], points[i-1]);
    }
    return length;
}

//===============================  Drawing functions(optional) ====================================
Rope1020::Rope1020(QString input)
    :RopeBase(input)
{
    image = QImage(640,480,QImage::Format_ARGB32);
    painter = new QPainter(&image);
    painter->translate(image.rect().center());
    painter->scale(10, 10);

    drawPoints(N, points, R);
    //drawRope(R, points, N);
    float length = calcRope(R, points, N);

    qDebug() << "length of the rope = " << length;



}

QPointF line_eq(QPointF A, QPointF B, float t)
{
    QPointF C;

    C.setX(A.x() + t * (B.x() - A.x()));
    C.setY(A.y() + t * (B.y() - A.y()));
    return C;
}


void Rope1020::drawPoints(int N, std::vector<QPointF>& points, float R)
{
    for(int i=0; i < N; i++)
    {
        painter->drawEllipse(points[i],R,R);
    }
}

QPointF Rope1020::getIntersectionPoint(float R, QPointF C1, QPointF C2)
{
    float t = (float)R / rasst(C1,C2);
    QPointF A = line_eq(C1,C2,t);
    return A;
}

QPointF Rope1020::rotatePointInCircle(QPointF A, QPointF C, float angle)
{
    QTransform t;
    t.translate(C.x(), C.y());
    t.rotate(angle);
    t.translate(-C.x(), -C.y());
    //t.translate(A.x(), A.y());
    QPointF B = A * t;
    return B;
}

void Rope1020::drawP(QPointF B, float R, QColor col)
{
    painter->setPen(col);
    painter->drawEllipse(B,R/4.,R/4.);
    painter->setPen(Qt::black);
}


float Rope1020::drawRope(float R, std::vector<QPointF> points, int N)
{
    std::vector<QPointF> lines;
    for(int i=1; i <= N; i++)
    {
        QPointF A = getIntersectionPoint(R, points[i], points[i-1]);
        //drawP(A, R, Qt::black);
        QPointF B = rotatePointInCircle(A, points[i], 90);
        //drawP(B, R, Qt::green);
        QPointF C = getIntersectionPoint(R, points[i], points[i+1]);
        //drawP(C, R, Qt::black);
        QPointF D = rotatePointInCircle(C, points[i], -90);
        //drawP(D, R, Qt::red);
        lines.push_back(B);
        lines.push_back(D);
    }

    lines.push_back(lines[0]);
    for(int i=0; i < lines.size()-1; i++)
    {
        if((i%2)==1)
        {
            painter->drawLine(lines[i],lines[i+1]);
        }
    }

}

