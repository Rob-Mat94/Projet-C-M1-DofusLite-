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
    Carte(const Carte &) = delete;
    Carte &operator=(const Carte &) = delete;
    virtual ~Carte();

    const int getWidth() const { return this->_width; }
    const int getHeight() const { return this->_height; }

    void addElement(Element *e);
    void removeElement(Element *e);

    // sert a bouger le guerrier
    bool canMove(Position oldPos, Position newPos) const;
    bool updatePos(Guerrier *g, Position oldPos, Position newPos);

    // renvoi le'enemi le plus proche
    Guerrier *checkEnemy(Guerrier *g);

    // sert a afficher la carte dans l'interface graphique
    std::vector<std::vector<char>> getMap() const;
    // sert a afficher la carte dans le terminal
    void printMap() const;

private:
    void init_map(std::ifstream &f);

    std::vector<std::vector<Element *>> _map;
    Game *_game;
    int _width;
    int _height;
};

#endif