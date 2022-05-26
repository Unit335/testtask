#ifndef UTILS_H
#define UTILS_H
#include <QVector>
#include <QPoint>
#include <cmath>

int isLeft(QPoint a, QPoint b, QPoint c);
QPoint rotateline(QPoint point, QPoint pivot, float angle);

#endif // UTILS_H
