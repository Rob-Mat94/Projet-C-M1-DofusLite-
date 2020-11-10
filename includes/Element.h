#ifndef ELEMENT_H
#define ELEMENT_H

#include "Position.h"
#include <string>

class Guerrier;

class Element
{
public:
    Element(Position pos = Position(0, 0));
    Element(const Element &element);
    virtual ~Element();

    /* Héritage  */
    virtual void setPosition(const Position &pos);
    virtual const Position &getPosition() const;
    virtual bool element_action(); // Action de l'élément

    /* pour futur ajout (armes, etc)*/
    virtual void pickUpElement(Guerrier *g){return;}
    /* Représentation (caractère pour l'instant) */
    virtual char getDraw() { return ' '; }
    //si vide dans le sens ou un guerrier peut traverser
    virtual bool isEmpty() { return true; }
    

protected:
    Position _pos;
};

#endif