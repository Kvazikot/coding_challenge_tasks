#ifndef DOMINO1509_H
#define DOMINO1509_H

#include "mainwindow.h"

class Knuckle
{
public:
    int   n1, n2;
    float angle;
    std::vector<QPointF> points;
    QRectF myRect;
    Knuckle(int n1, int n2);
    Knuckle(int n1, int n2, float a);
    Knuckle(int n_points);
    void GeneratePoints(int n, bool first);
    void setAngle(float angle){ this->angle = angle; }


};

class Domino1509 : public QObject
{
    Q_OBJECT
public:
    MainWindow* mw;
    Domino1509(MainWindow* mw);
public slots:
    void slotKeyPress(int key);
};

#endif // DOMINO1509_H
