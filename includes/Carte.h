#ifndef CARTE_H
#define CARTE_H

#include "Element.h"
#include "Guerrier.h"
#include "Obstacle.h"
#include "ObjetRamassable.h"
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
    void removeElement(Element *e);
    void printMap() const;

    bool canMove(Position oldPos, Position newPos);
    bool updatePos(Guerrier *g, Position oldPos, Position newPos);

    static auto &getTeam_1() { return _team_1; }
    static auto &getTeam_2() { return _team_2; }

    Guerrier *CheckEnemy(Guerrier *g);

private:
    static std::vector<Guerrier *> _team_1;
    static std::vector<Guerrier *> _team_2;

    void init_map(std::ifstream &f);
    int _width;
    int _height;
    std::vector<std::vector<Element *>> _map;
};

#endif