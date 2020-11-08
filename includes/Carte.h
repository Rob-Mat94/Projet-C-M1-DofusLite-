#ifndef CARTE_H
#define CARTE_H

#include "Element.h"
#include "Guerrier.h"
#include "ObjetRamassable.h"
#include "Obstacle.h"
#include <vector>
#include <fstream>

class Guerrier;

class Carte
{
public:
    Carte();
    Carte(std::string file_name);
    virtual ~Carte();

    const int getWidth() const { return this->_width; }
    const int getHeight() const { return this->_height; }

    void addElement(Element *e);
    void printMap() const;

    /* Polymorphisme à voir */
    bool can_Move(Guerrier *g, Direction &d);
    void moveG(Guerrier *g, Direction &d);
    bool canPick_up(Guerrier *g, ObjetRamassable *obj_r);
    void Pick_up(Guerrier *g);

    //test move guerrier
    bool updatePos(Position oldPos, Position newPos);
    Guerrier *guerrier;

private:
    void init_map(std::ifstream &f);

    int _width;
    int _height;
    std::vector<std::vector<Element *>> _map;
};

#endif