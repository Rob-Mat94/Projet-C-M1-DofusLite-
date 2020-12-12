#ifndef GAME_H
#define GAME_H

#include <map>
#include "Carte.h"
#include "Team.h"

class Team;
class Carte;

class Game
{

public:
    Game() = default;
    Game(std::string file);
    virtual ~Game() = default;

    Team *getCurrentTeam();
    Guerrier *getCurrent();
    void addGuerrier(Guerrier *g);
    void removeGuerrier(Guerrier *g);
    void increment();
    void step();
    void start();

private:
    Carte *carte;
    std::map<std::string, Team *> teamList = {};
    int currentTeam = 0;
    bool running = true;
};

#endif