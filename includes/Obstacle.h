#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Element.h"

class Obstacle : public Element
{
public:
    Obstacle(Position pos = Position(0, 0));
    virtual ~Obstacle();
    virtual bool element_action(Element *e);

    /* Méthodes héritées */
    /* Représentation (caractère pour l'instant) */
    char getDraw() const { return '*'; }
    bool isEmpty() const { return false; }
};

#endif