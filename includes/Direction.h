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
    int x;
    int y;
};

Coordinate getDirCoordinate(Direction dir);

#endif