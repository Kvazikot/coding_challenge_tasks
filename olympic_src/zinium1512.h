#ifndef ZINIUM1512_H
#define ZINIUM1512_H

#include "mainwindow.h"

enum CellState {NIL=0, FREE=1, BLACK=2, RED=3};

struct Cell
{
    int i;
    int j;
    CellState state;
    Cell()
    {
        i=-1; j=-1; state = NIL;
    }

    Cell(int i, int j, CellState state)
        :i(i),j(j),state(state)
    {}

    bool isQueen() { return (state == CellState::BLACK) ||  (state == CellState::RED);}

};

class Zinium1512
{
public:
    Zinium1512(MainWindow* mw);
    Cell nil_cell;
    std::vector<Cell*> cells;
    std::map<std::pair<int,int>, Cell* > cell_map;
    Cell* getCell(int i, int j);
    void drawCells(QPainter& painter, int RES);
    bool checkQueen(Cell* cell);
    void createImage(MainWindow* mw);
    void clear();
    Cell* getRandFreePos();
};

#endif // ZINIUM1512_H
