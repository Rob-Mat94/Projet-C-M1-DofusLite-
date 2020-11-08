#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "../includes/Element.h"

class Obstacle : public Element
{
public:
    Obstacle(Position pos = Position(0, 0));
    virtual ~Obstacle();
    bool element_action();

    /* Représentation (caractère pour l'instant) */
    virtual char getDraw() { return '*'; }
};

#endif