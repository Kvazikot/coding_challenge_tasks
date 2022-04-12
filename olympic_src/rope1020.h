#ifndef ROPE1020_H
#define ROPE1020_H

#include <QString>
#include <QImage>
#include <QPainter>

class RopeBase
{
public:
    int N;
    float R;

    RopeBase(QString input);
    float calcRope(float R, std::vector<QPointF> points, int N);
    float calcArcLength(QPointF A, QPointF C, QPointF B, float R);
    float rasst(QPointF p1, QPointF p2);

    std::vector<QPointF> points;
};

class Rope1020 : RopeBase
{
public:
    QImage image;
    Rope1020(QString input);
    void drawPoints(int N, std::vector<QPointF>& points, float R);
    QPointF getIntersectionPoint(float R, QPointF C1, QPointF C2);
    float drawRope(float R, std::vector<QPointF> points, int N);
    QPointF rotatePointInCircle(QPointF A, QPointF C, float angle);
    void drawP(QPointF B, float R, QColor col);
private:
    QPainter* painter;

};

#endif // ROPE1020_H
