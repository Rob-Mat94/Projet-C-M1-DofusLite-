#include "../includes/Obstacle.h"

Obstacle::Obstacle(Position pos) : Element(pos) {}

Obstacle::~Obstacle() {}

bool Obstacle::element_action(Element *e)
{
    return false;
}