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
    Game(const Game &) = delete;
    Game &operator=(const Game &) = delete;

    virtual ~Game();
    void addGuerrier(Guerrier *g);
    void removeGuerrier(Guerrier *g);
    void reset();
    void reset(std::string file);

    // utilisée en cas d'affichage en terminal
    void start();

    std::vector<std::vector<char>> getMap() const;
    Guerrier *getCurrent();
    Guerrier *getEnemy();
    std::string getWinner() const;
    bool isRunnig() const;
    int getHeight() const;
    int getWidth() const;
    void increment();
    void isGameOver();
    bool step(char key);
    void decrementPM();

private:
    enum OS
    {
        Windows,
        Linux
    };
    static const OS MY_OS;
    static const int PM = 4;

    Team *getCurrentTeam();
    auto getEmptyTeam();
    void deleteAll();
    bool step();

    Carte *_carte;
    std::string _file;
    std::map<std::string, Team *> _teamList = {};

    int _currentTeam = 0, _pm = Game::PM;
    bool _running = true;
};

#endif