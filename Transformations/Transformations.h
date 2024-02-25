#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "../Structs/Point.h"

Point translatePoint(Point& p, double x, double y);
Point scalePoint(Point& p, double W, double H);
Point rotatePoint(Point& p, float angle); 
Point skewPointX(Point& p, float angle);
Point skewPointY(Point& p, float angle);
Point reflectPointOrigin(Point& p);
Point reflectPointX(Point& p); 
Point reflectPointY(Point& p);

#endif