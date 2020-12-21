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
    virtual ~Game();
    void addGuerrier(Guerrier *g);
    void removeGuerrier(Guerrier *g);
    void reset();
    void reset(std::string file);

    std::vector<std::vector<char>> getMap();
    Guerrier *getCurrent();
    Guerrier *getEnemy();
    std::string getWinner();
    void increment();
    void isGameOver();
    bool isRunnig();
    int getHeight();
    int getWidth();

    bool step();
    bool step(char key);
    void start();

private:
    Team *getCurrentTeam();
    auto getEmptyTeam();
    void deleteAll();

    Carte *carte;
    std::string _file;

    std::map<std::string, Team *> teamList = {};
    int currentTeam = 0;
    bool running = true;
};

#endif