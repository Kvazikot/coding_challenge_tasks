#include <QPainter>
#include <QDebug>
#include <QElapsedTimer>
#include "zinium1512.h"

void Zinium1512::createImage(MainWindow* mw)
{
    int RES = 800;
    QImage image(RES+10, RES+10, QImage::Format_ARGB32);
    QPainter painter(&image);
    image.fill(Qt::white);
    painter.setPen(Qt::red);
    drawCells(painter, RES);
    mw->setImage(image);
}

Zinium1512::Zinium1512(MainWindow* mw)
{
    const int N = 8;
    for(int j=0; j<N; j++)
    for(int i=0; i<N; i++)
    {
        Cell* cell = new Cell(i,j,FREE);
        Cell* cell2 = new Cell(i,j,FREE);
        cells.push_back(cell);
        cell_map[std::make_pair(i,j)] = cell;
    }

    //расставить ферзей
    int x0, y0;
    /*for(int i=0; i < 4; i++)
    {
        int x = rand()%8;
        int y = rand()%8;
        getCell(x,y)->state = CellState::BLACK;
        x0 = x; y0 = y;
    }*/

    getCell(2,1)->state = CellState::BLACK;
    getCell(1,2)->state = CellState::BLACK;

    Cell* selc = getCell(2,1);
    selc->state = RED;
    qDebug() <<  checkQueen(selc);

    QElapsedTimer timer;

    timer.start();

    int iters = 100000;
    int n=0;
    while(--iters!=0)
    {
        Cell* randc = getCell(rand()%8, rand()%8);
        if( checkQueen(randc) && randc->state == CellState::FREE )
        {
          randc->state = CellState::BLACK;
          n++;
        }
        if(n == 8)
            break;
        if((iters%100) == 0)
        {
            n = 0;
            clear();
        }
    }

    qDebug() << "iters " << iters;
    qDebug() << "timer " << timer.elapsed();

    //создать изображение пересекающихся кругов
    createImage(mw);
}

Cell* Zinium1512::getRandFreePos()
{
    while(1)
    {
        int i,j;
        i = rand()%8;
        j = rand()%8;
        Cell* c = getCell(i,j);
        if( c->state ==  CellState::FREE)
            return c;
    }
}

void Zinium1512::clear()
{
    for(int i=0; i < 8; i++)
        for(int j=0; j < 8; j++)
            getCell(i,j)->state = CellState::FREE;
}

bool Zinium1512::checkQueen(Cell* cell)
{
    //горизонталь
    for(int i=cell->i+1; i < 8; i++)
        if( getCell(i,cell->j)->state != CellState::FREE  )
            return false;
    for(int i=0; i < cell->i; i++)
        if( getCell(i,cell->j)->state != CellState::FREE  )
            return false;

    //вертикаль
    for(int j=cell->j+1; j < 8; j++)
        if( getCell(cell->i,j)->state != CellState::FREE  )
            return false;
    for(int j=0; j < cell->j; j++)
        if( getCell(cell->i,j)->state != CellState::FREE  )
            return false;

    // диогонали
    Cell* c = cell;
    while(c!=&nil_cell)
    {
        c = getCell(c->i+1, c->j+1);
        if( c->isQueen() )
            return false;
    }

    c = cell;
    while(c!=&nil_cell)
    {
        c = getCell(c->i-1, c->j-1);
        if( c->isQueen() )
            return false;
    }
    c = cell;
    while(c!=&nil_cell)
    {
        c = getCell(c->i+1, c->j-1);
        if( c->isQueen() )
            return false;
    }
    c = cell;
    while(c!=&nil_cell)
    {
        c = getCell(c->i-1, c->j+1);
        if( c->isQueen() )
            return false;
    }


    return true;

}

Cell* Zinium1512::getCell(int i, int j)
{
    std::pair<int,int> key = std::make_pair(i,j);
    if( cell_map.find(key)!=cell_map.end() )
    {
        return cell_map[key];
    }
    else
        return &nil_cell;
}


void Zinium1512::drawCells(QPainter& painter, int RES)
{
    //draw vertical lines
    int N = 8;
    int cell_size = 10; //pixels

    cell_size = RES / N;
    int x = 0;
    painter.setPen(Qt::black);
    for(int j=0; j < N; j++)
    {
        painter.drawLine(QPointF(x,0), QPointF(x,RES));
        x+=cell_size;

    }

    //draw horizontal lines
    int y = 0;
    for(int j=0; j < N; j++)
    {
        painter.drawLine(QPointF(0,y), QPointF(RES,y));
        y+=cell_size;
    }


    int x0 = 0;
    int y0 = 0;
    for(int i=0; i < N; i++)
    for(int j=0; j < N; j++)
    {
        Cell* cell = getCell(i, j);
        switch( cell->state )
        {
            case CellState::NIL:
            break;
            case CellState::BLACK:
            {
              QPainterPath path;
              path.addEllipse(i*cell_size+x0, j*cell_size+y0, cell_size, cell_size);
              painter.fillPath(path, Qt::black);
              painter.drawPath(path);
            }
            break;
            case CellState::RED:
            {
                QPainterPath path;
                path.addEllipse(i*cell_size+x0, j*cell_size+y0, cell_size, cell_size);
                painter.fillPath(path, Qt::red);
                painter.drawPath(path);
            }
            break;

        }
    }


}
