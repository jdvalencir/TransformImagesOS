#include "Transformations/Transformations.h"
#include <cmath>

Point translatePoint(Point& p, double x, double y){    
    p.x += x;
    p.y += y;
    return p;
}

Point scalePoint(Point& p, double W, double H) {
    p.x *= W;
    p.y *= H;
    return p;
}

Point rotatePoint(Point& p, float angle){
    Point rotatedPoint; 
    rotatedPoint.x = p.x * cos(angle) - p.y * sin(angle); 
    rotatedPoint.y = p.x * sin(angle) + p.y * cos(angle);
    return rotatedPoint;
}

Point skewPointX(Point& p, float angle){
    Point skewPoint;
    skewPoint.x = p.x * 1 + p.y * tan(angle);
    skewPoint.y = p.x * 0 + p.y * 1;
    return skewPoint;
}

Point skewPointY(Point& p, float angle){
    Point skewPoint; 
    skewPoint.x = p.x * 1 + p.y * 0;
    skewPoint.y = p.x * tan(angle) + p.y * 1;
    return skewPoint;
}

Point reflectPointOrigin(Point& p){
    p.x *= -1;
    p.y *= -1;
    return p; 
}

Point reflectPointX(Point& p){
    
}

Point reflectPointY(Point& p){

}
