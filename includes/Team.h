#ifndef TEAM_H
#define TEAM_H

#include <list>
#include "Guerrier.h"

class Game;
class Guerrier;

class Team
{

public:
    Team() : _list({}), current(0){};
    virtual ~Team() = default;
    void addGuerrier(Guerrier *g);
    void removeGuerrier(Guerrier *g);
    Guerrier *getCurrent();
    void increment();
    int guerriersRestants() { return _list.size(); };

private:
    std::list<Guerrier *> _list;
    int current;
};

#endif