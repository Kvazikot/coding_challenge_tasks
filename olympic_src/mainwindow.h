#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void setImage(QImage& image);
    void keyPressEvent(QKeyEvent *event);
signals:
    void on_keypress(int key);
};

#endif // MAINWINDOW_H
