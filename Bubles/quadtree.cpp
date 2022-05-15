#include "quadtree.h"
#define _USE_MATH_DEFINES
#include <math.h>

bool AABB::containsPoint(XY p)
{
    float xmin = center.x - halfDimension.x;
    float xmax = center.x + halfDimension.x;
    float ymin = center.y - halfDimension.y;
    float ymax = center.y + halfDimension.y;

    if( ( p.x >= xmin) && (p.x <= xmax) &&  ( p.y >= ymin) && (p.y <= ymax) )
       return true;
    else
       return false;
}

bool AABB::intersectsAABB(AABB other)
{
    float xmin = other.center.x - other.halfDimension.x;
    float ymin = other.center.y - other.halfDimension.y;
    float xmax = other.center.x + other.halfDimension.x;
    float ymax = other.center.y + other.halfDimension.y;
    if( containsPoint(XY(xmin,ymin)) )
        return true;
    if( containsPoint(XY(xmax,ymax)) )
        return true;
    if( containsPoint(XY(xmin,ymax)) )
        return true;
    if( containsPoint(XY(xmax,ymin)) )
        return true;
    return false;
}

// вставить окружность
bool QuadTree::insertCircleAsPoints(XY center, int radius, int max_level)
{
    float x,y;
    float dr = radius / 10.;
    for(float r=radius; r > 0; r-=dr)
    for(float angle=0; angle <= M_PI*2; angle+=M_PI/20.)
    {
        x = center.x + r * cos(angle);
        y = center.y + r * sin(angle);
        insert(XY(x,y),max_level);
    }
    insert(XY(center.x,center.y),max_level);
    return true;
}

void QuadTree::draw(QPainter& painter)
{
    for (unsigned p = 0; p < points.size(); p++)
    {
        painter.drawEllipse(points[p].x-2,points[p].y-2,2,2);
    }
    if(northWest!=0)
    {
        northWest->draw(painter);
        northEast->draw(painter);
        southWest->draw(painter);
        southEast->draw(painter);
    }
}

bool  QuadTree::insertCircle(Circle cir)
{
    insert(XY(cir.xc,cir.yc-cir.r,cir.r));
    insert(XY(cir.xc,cir.yc+cir.r,cir.r));
    insert(XY(cir.xc+cir.r,cir.yc,cir.r));
    insert(XY(cir.xc-cir.r,cir.yc,cir.r));
    return insert(XY(cir.xc,cir.yc,cir.r));
}

// Вставить точку
bool QuadTree::insert(XY p, int max_level)
{
  // Игнорировать объекты, не принадлежащие дереву
  if (!boundary.containsPoint(p))
    return false; // Объект не может быть добавлен

  // Если есть место, осуществить вставку
  if (points.size() < QT_NODE_CAPACITY)
  {
    points.push_back(p);
    return true;
  }

  // Далее необходимо разделить область и добавить точку в какой-либо узел
  if (northWest == 0)
    subdivide();

  if (northWest->insert(p,max_level)) return true;
  if (northEast->insert(p,max_level)) return true;
  if (southWest->insert(p,max_level)) return true;
  if (southEast->insert(p,max_level)) return true;

  // По каким-то причинам вставка может не осуществиться (чего на самом деле не должно происходить)
  return false;
}

void QuadTree::subdivide()
{
    XY center = XY(boundary.center.x-boundary.halfDimension.x/2,
                   boundary.center.y-boundary.halfDimension.y/2);
    XY halfDimension = XY(boundary.halfDimension.x/2,boundary.halfDimension.y/2);
    northWest = new QuadTree(AABB(center,halfDimension));
    northWest->level = level + 1;
    center = XY(boundary.center.x+boundary.halfDimension.x/2,
                boundary.center.y-boundary.halfDimension.y/2);
    northEast = new QuadTree(AABB(center,halfDimension));
    northEast->level = level + 1;
    center = XY(boundary.center.x-boundary.halfDimension.x/2,
                boundary.center.y+boundary.halfDimension.y/2);
    southWest = new QuadTree(AABB(center,halfDimension));
    southWest->level = level + 1;
    center = XY(boundary.center.x+boundary.halfDimension.x/2,
                boundary.center.y+boundary.halfDimension.y/2);
    southEast = new QuadTree(AABB(center,halfDimension));
    southEast->level = level + 1;
}

std::vector<XY> QuadTree::queryRange(AABB range)
{
    // Подготовить массив под результат
    std::vector<XY> pointsInRange;

    // Отмена, если диапазон не совпадает с квадрантом
    if (!boundary.intersectsAABB(range))
       return pointsInRange; // Пустой список

    // Проверить объекты текущего уровня
    for (unsigned p = 0; p < points.size(); p++)
    {
      if (range.containsPoint(points[p]))
        pointsInRange.push_back(points[p]);
    }

    // Остановка, если больше нет потомков
    if (northWest == 0)
      return pointsInRange;

    // Добавить все точки потомков
    std::vector<XY> points = northWest->queryRange(range);
    pointsInRange.insert(pointsInRange.begin(),points.begin(), points.end());
    points = northEast->queryRange(range);
    pointsInRange.insert(pointsInRange.begin(),points.begin(), points.end());
    points = southWest->queryRange(range);
    pointsInRange.insert(pointsInRange.begin(),points.begin(), points.end());
    points = southEast->queryRange(range);
    pointsInRange.insert(pointsInRange.begin(),points.begin(), points.end());


    return pointsInRange;
}

