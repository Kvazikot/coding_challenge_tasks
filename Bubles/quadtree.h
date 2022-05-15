#ifndef QUADTREE_H
#define QUADTREE_H

#include "circles.h"
#include <math.h>
#include <vector>
#include <QPainter>

// Простая структура для представления точки или вектора
struct XY
{
  float x;
  float y;
  float r;

  XY(){}
  XY(float _x, float _y):x(_x),y(_y){}
  XY(float _x, float _y, float r):x(_x),y(_y),r(r){}
  float distTo(XY p)
  {
      return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y));
  }
};

// Ограничивающий параллелепипед, выровненный по координатным осям
// (axis-aligned bounding box, AABB), половинной размерности с центром
struct AABB
{
  XY center;
  XY halfDimension;

  AABB(XY center, XY halfDimension):center(center), halfDimension(halfDimension)
  {}
  bool containsPoint(XY p);  
  bool intersectsAABB(AABB other);
};

class QuadTree
{
public:
  // Константа — количество элементов, которые можно хранить в одном узле
  static const int QT_NODE_CAPACITY = 4;

  // Ограничивающий параллелепипед, выровненный по координатным осям,
  // показывает границы дерева
  AABB boundary;

  // Точки
  std::vector<XY> points;

  // Потомки
  QuadTree* northWest;
  QuadTree* northEast;
  QuadTree* southWest;
  QuadTree* southEast;

  // Глубина дерева
  int level;

  // Методы
  QuadTree(AABB _boundary):boundary(_boundary)
  {
      northWest = northEast = southWest = southEast = 0;
      level = 0;
  }
  bool insert(XY p, int max_level=1000);
  bool insertCircle(Circle cir);
  bool insertCircleAsPoints(XY center, int radius, int max_level=1000);
  std::vector<XY> queryRange(AABB range);
  void subdivide(); // Создание 4 потомков, делящих квадрант на 4 равные части
  void draw(QPainter& painter);

};

#endif // QUADTREE_H
