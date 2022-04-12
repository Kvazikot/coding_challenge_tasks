#ifndef SQUAREFRAMES1006_H
#define SQUAREFRAMES1006_H

#include <QString>
#include <QImage>

class SquareFrames1006
{
public:
    QImage image;
    int res_x, res_y;
    SquareFrames1006(QString filename);
    int  findFrames(QImage& image);
    void PrepareMask(QImage& mask, uchar symbol, int fontSize);
    void findHorLines(QImage& image, std::vector<QLine>& hor_lines);
    void findCorners(std::vector<QLine>& hor_lines, QImage& image, std::vector<QPoint> lu_corners);
    void fillGups(std::vector<QLine>& hor_lines, QImage& image);
    void cutAlpha(QRgb& p);
};

#endif // SQUAREFRAMES1006_H
