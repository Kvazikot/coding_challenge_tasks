#include <random>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QTime>
#include "mainwindow.h"
#include "circles.h"
#include "quadtree.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    frame = 0;
    startTimer(100);
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    repaint();
}

void Circle_draw(Circle cir, QPainter& painter)
{
    QPainterPath path;
    path.addEllipse(QRect(cir.xc-cir.r,cir.yc-cir.r,2*cir.r,2*cir.r));
    QRadialGradient radialGrad(QPointF(cir.xc, cir.yc), 2*cir.r);
    radialGrad.setColorAt(0, Qt::white);
    radialGrad.setColorAt(0.5, qRgba(0,0,255,0));
    radialGrad.setColorAt(1, Qt::white);
    painter.fillPath(path, QBrush(radialGrad));
}

QImage MainWindow::generateBubblesImage(int width, int height, int Nbubles, int maxRadius)
{
    QImage image(width, height, QImage::Format_ARGB32);
    QPainter painter(&image);
    QPen pen(Qt::red);
    int distribution[] = {150,50,200,300,300};
    std::uniform_int_distribution<int> distribution_coord(0,width);
    std::uniform_real_distribution<float> distribution_rad(0.,1.);
    double radiuses[] = {50,30,20,10,5};
    std::default_random_engine gen;
    gen.seed(QTime::currentTime().msecsSinceStartOfDay());
    painter.fillRect(rect(), Qt::blue);
    Circles circles;

    long count=0,colisions=0;
    for(int ri=0; ri < 5; ri++)
    {
        double r = radiuses[ri];
        int N = Nbubles * distribution[ri] / 1000;
        for(int i=0; i < N; i++)
        {
            int x = distribution_coord(gen);
            int y = distribution_coord(gen);
            Circle cir = Circle(r,x,y);
            if(circles.add_not_intersect(cir))
            {
//               Circle_draw(cir,?/r);
               count++;
            }
            else
                colisions++;
        }
    }
    qDebug() << "count=" << count << " from " << Nbubles << " colisions=" << colisions;
    return image;
}

void MainWindow::TestdrawCircle(QuadTree* quadtree, int x, int y, int r)
{
    QPainter painter(this);
    qDebug() << (x)*(y)/r;
    std::vector<XY> points_in_range = quadtree->queryRange(AABB(XY(x,y),XY(r,r)));
    if( points_in_range.size() == 0 )
      if( quadtree->insertCircleAsPoints(XY(x,y),r) )
      {
        painter.drawEllipse(x-r,y-r,2*r,2*r);
      }
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    QImage image = generateBubblesImage(rect().width(), rect().height(), 5000, rect().height()/10);
    painter.drawImage(rect(),image);
    //image.save("bubbles"+QString::number(frame)+".png");
    frame++;

    return;
    QuadTree* quadtree = new QuadTree(AABB(XY(rect().center().x(),rect().center().y()),
                                           XY(rect().width()/2,rect().height()/2)));

    qDebug() << "window size=" << rect();

    // Test 1 intersection center circle and small inside
    TestdrawCircle(quadtree, rect().center().x(),rect().center().y(), 50);
    TestdrawCircle(quadtree, rect().center().x()+101,rect().center().y(), 60);
    TestdrawCircle(quadtree, rect().center().x()-101,rect().center().y(), 60);
    TestdrawCircle(quadtree, rect().center().x(),rect().center().y()+101, 60);
    TestdrawCircle(quadtree, rect().center().x(),rect().center().y()-101, 60);
    return;

    // Test 2 intersection with random coordinates
    std::uniform_int_distribution<int> distribution_coord(50,400);
    std::default_random_engine gen;
    for(int i=0; i < 1000; i++)
    {
        int x = distribution_coord(gen);
        int y = distribution_coord(gen);
        TestdrawCircle(quadtree,x,y,50);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

