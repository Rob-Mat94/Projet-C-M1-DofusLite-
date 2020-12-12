#ifndef CARTE_H
#define CARTE_H

#include <vector>
#include <fstream>
#include "ObjetRamassable.h"
#include "Element.h"
#include "Guerrier.h"
#include "Obstacle.h"
#include "Game.h"

class Guerrier;
class Game;

class Carte
{
public:
    Carte(std::string file_name, Game *game);
    virtual ~Carte();

    const int getWidth() const { return this->_width; }
    const int getHeight() const { return this->_height; }

    void addElement(Element *e);
    void removeElement(Element *e);
    void printMap() const;

    bool canMove(Position oldPos, Position newPos);
    bool updatePos(Guerrier *g, Position oldPos, Position newPos);

    Guerrier *CheckEnemy(Guerrier *g);

private:
    void init_map(std::ifstream &f);

    std::vector<std::vector<Element *>> _map;
    Game *_game;
    int _width;
    int _height;
};

#endif