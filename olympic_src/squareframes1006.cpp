#include <QTextCodec>
#include <QPainter>
#include <QDebug>
#include "squareframes1006.h"

SquareFrames1006::SquareFrames1006(QString filename)
{
    res_x = 50;
    res_y = 20;
    if( image.load(filename) )
    {
        findFrames(image);
    }

}

void SquareFrames1006::cutAlpha(QRgb& p)
{
    int r = qRed(p);
    int g = qGreen(p);
    int b = qBlue(p);
    p = qRgb(qRed(p), qGreen(p), qBlue(p));
}

void SquareFrames1006::findHorLines(QImage& image, std::vector<QLine>& hor_lines)
{
    int countBlack=0;
    for(int j=0; j < image.height(); j++)
    for(int i=0; i < image.width(); i++)
    {
        QRgb p = image.pixel(i, j);
        cutAlpha(p);

        if( p == QColor(Qt::black).rgb() )
        {
            countBlack++;
        }
        else if( p == QColor(Qt::white).rgb() )
        {
            //if(countBlack != 0)
            //    qDebug() << countBlack;
            if( countBlack > 2 )
            {
                QLine line(i-countBlack,j,i,j);
                hor_lines.push_back(line);
            }
            countBlack = 0;

        }
    }
}

void SquareFrames1006::fillGups(std::vector<QLine>& hor_lines, QImage& image)
{
    int n_gups=0;
    int countBlack=0;
    int countBlack2=0;
    for(auto l=hor_lines.begin(); l!=hor_lines.end(); l++)
    {
        QLine line = *l;
        int i = line.x1();
        countBlack = 0;
        countBlack2 = 0;
        for(int j=0; j < 5; j++)
        {
            QRgb p = image.pixel(i, line.y1() + j);
            cutAlpha(p);
            if( p == QColor(Qt::black).rgb() )
            {
                countBlack++;
            }
            p = image.pixel(i, line.y1() - j);
            cutAlpha(p);
            if( p == QColor(Qt::black).rgb() )
            {
                countBlack2++;
            }

        }
        if(countBlack < 4 && countBlack2 < 4)
        {
            auto l2 = l;
            if(l2!=hor_lines.begin())
            {
                l2--;
                qDebug() << (*l2);
                (*l2).setP2(line.p2());
                qDebug() << (*l2);
                n_gups++;
            }

        }

    }

    qDebug() << "n_gups " << n_gups;
}

void SquareFrames1006::findCorners(std::vector<QLine>& hor_lines, QImage& image, std::vector<QPoint> lu_corners)
{
    int countBlack=0;
    float kx = (float)image.width() / res_x;
    float ky = (float)image.height() / res_y;
    //find right upper corners
    for(auto l=hor_lines.begin(); l!=hor_lines.end(); l++)
    {
        QLine line = *l;
        int i = line.x1();
        countBlack = 0;
        for(int j=0; j < 5; j++)
        {
            QRgb p = image.pixel(i, line.y1() + j);
            cutAlpha(p);
            if( p == QColor(Qt::black).rgb() )
            {
                countBlack++;
            }
        }
        if(countBlack > 4)
        {
            lu_corners.push_back(line.p1());
            qDebug() << qRound((float)line.x1()/kx-1) << " " << qRound(line.y1()/ky) << " " << qRound((line.x2() - line.x1())/kx);
        }

    }
    qDebug() << "num lu corners = " << lu_corners.size();
}

int  SquareFrames1006::findFrames(QImage& image)
{
    int countBlack = 0;
    std::vector<QLine> hor_lines;
    //  поиск горизонтальных линий
    findHorLines(image, hor_lines);
    //qDebug() << "num hor lines = " << hor_lines.size();
    fillGups(hor_lines, image);
    std::vector<QPoint> lu_corners;
    findCorners(hor_lines, image, lu_corners);

}

