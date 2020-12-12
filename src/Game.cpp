#include "../includes/Game.h"
#include "../includes/terminalSetting.h"
#include "../includes/Carte.h"
#include "../includes/Team.h"

Game::Game(std::string file)
{
    carte = new Carte(file, this);
}

Guerrier *Game::getCurrent()
{
    return getCurrentTeam()->getCurrent();
}

void Game::increment()
{
    getCurrentTeam()->increment();
    currentTeam = ++currentTeam % teamList.size();
}

Team *Game::getCurrentTeam()
{
    if (teamList.empty())
        return nullptr;
    auto it = teamList.begin();
    std::advance(it, currentTeam);

    return (*it).second;
}

void Game::addGuerrier(Guerrier *g)
{
    if (teamList.find(g->getTeam()) == teamList.end())
        teamList[g->getTeam()] = new Team();
    teamList[g->getTeam()]->addGuerrier(g);
}

void Game::removeGuerrier(Guerrier *g)
{
    teamList[g->getTeam()]->removeGuerrier(g);
}

void Game::step()
{
    switch (getKey())
    {
    case 'e':
        running = false;
        break;
    case 'z':
        getCurrent()->move(Up, *carte);
        break;
    case 's':
        getCurrent()->move(Down, *carte);
        break;
    case 'q':
        getCurrent()->move(Left, *carte);
        break;
    case 'd':
        getCurrent()->move(Right, *carte);
        break;
    default:
        step();
        break;
    }
}

void Game::start()
{
    while (running)
    {
        system("clear");
        carte->printMap();
        step();
        increment();
    }
}