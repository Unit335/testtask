#include "utils.h"
#define PI 3.14159265


QPoint rotateline(QPoint point, QPoint pivot, float angle){
    //point: one of the points on line
    //pivot: point on the line relative to which line will be rotated
    //angle: angle of rotation
    //return new point after rotating line
    QPoint res;
    float s = sin(angle*PI/180);
    float c = cos(angle*PI/180);
    res.setX(pivot.x() + (c * (point.x() - pivot.x())
            +(-s * (point.y() - pivot.y()))));
    res.setY(pivot.y() + (s * (point.x() - pivot.x())
            +(c * (point.y() - pivot.y()))));
    return res;
}

int isLeft(QPoint a, QPoint b, QPoint c){
    /*
    a,b - points on line
    c - point to check
    0: points are collinear
    1: point is on the left
    -1: point is on the right
    */
    int ch_state = ((b.x() - a.x())*(c.y() - a.y()) - (b.y() - a.y())*(c.x() - a.x()));
    if (ch_state == 0) {
        return 0;
    }
    else if (ch_state > 0) {
        return 1;
    }
    else {
        return -1;
    }
}

