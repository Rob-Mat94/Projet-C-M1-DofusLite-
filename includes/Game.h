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
    Game(std::string file);
    virtual ~Game() = default;
    void addGuerrier(Guerrier *g);
    void removeGuerrier(Guerrier *g);
    void start();

private:
    Guerrier *getCurrent();
    Team *getCurrentTeam();
    auto getEmptyTeam();
    std::string getWinner();
    void increment();
    void isGameOver();
    bool step();

    std::map<std::string, Team *> teamList = {};
    Carte *carte;
    int currentTeam;
    bool running;
};

#endif