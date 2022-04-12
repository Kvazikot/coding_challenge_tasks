#include <QKeyEvent>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);
}

void MainWindow::setImage(QImage& image)
{
    label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    emit on_keypress(event->key());
}
