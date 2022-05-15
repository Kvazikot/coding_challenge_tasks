#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QTimerEvent>
#include <quadtree.h>
#include <algorithm>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int frame;
    MainWindow(QWidget *parent = nullptr);
    QImage generateBubblesImage(int width, int height, int Nbubles, int maxRadius);
    void paintEvent(QPaintEvent* event);
    void timerEvent(QTimerEvent* event);
    ~MainWindow();
    void TestdrawCircle(QuadTree* quadtree, int x, int y, int r);
    
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
