#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction
{
    Up,
    Down,
    Left,
    Right
};

struct Coordinate
{
    int _x;
    int _y;
};

Coordinate getDirCoordinate(Direction dir);

#endif