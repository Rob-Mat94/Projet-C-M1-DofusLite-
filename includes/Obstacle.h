#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Element.h"

class Obstacle : public Element
{
public:
    Obstacle(Position pos = Position(0, 0));
    virtual ~Obstacle();
    virtual bool element_action();

    /* Représentation (caractère pour l'instant) */
    virtual char getDraw() { return '*'; }
    virtual bool isEmpty() { return false; }
    virtual bool isPickable() { return false; }
};

#endif