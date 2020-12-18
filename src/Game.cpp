#include "../includes/Game.h"
#include "../includes/terminalSetting.h"
#include "../includes/Carte.h"
#include "../includes/Team.h"

Game::Game(std::string file)
{
    this->currentTeam = 0;
    this->running = true;
    carte = new Carte(file, this);
}

Guerrier *Game::getCurrent()
{
    return getCurrentTeam()->getCurrent();
}

auto Game::getEmptyTeam()
{
    for (auto it = teamList.begin(); it != teamList.end(); it++)
    {
        if (it->second->guerriersRestants() <= 0)
            return it;
    }
    return teamList.end();
}

void Game::increment()
{
    if (getEmptyTeam() != teamList.end())
        teamList.erase(getEmptyTeam());
    getCurrentTeam()->increment();
    currentTeam++;
    currentTeam = currentTeam % teamList.size();
}

Team *Game::getCurrentTeam()
{
    if (teamList.empty())
        return nullptr;

    currentTeam = currentTeam % teamList.size();
    auto it = teamList.begin();
    std::advance(it, currentTeam);

    return it->second;
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

bool Game::step()
{
    return step(getKey());
}

bool Game::step(char key)
{
    switch (key)
    {
    case 'e':
        running = false;
        return true;
    case 'z':
        return getCurrent()->move(Up, carte);
    case 's':
        return getCurrent()->move(Down, carte);
    case 'q':
        return getCurrent()->move(Left, carte);
    case 'd':
        return getCurrent()->move(Right, carte);
    case 'y':
        return getCurrent()->Attack(carte->CheckEnemy(getCurrent()), carte);
    default:
        return false;
    }
}

// 2 Méthodes qui servent à afficher les infos à propos du guerrier
auto printInfo = [](Guerrier *g, int &pm) -> void {
    std::cout << "Appuyez sur 'e' pour quitter, z, q, s, d, pour bouger, y pour attaquer\n";
    std::cout << g->getName()
              << ": HP -> " << g->getHp()
              << ": PM -> " << pm
              << ": Attack -> " << g->getCapAttack()
              << ": Defense -> " << g->getCapDef()
              << ": Team -> " << g->getTeam()
              << "\n";
};

auto printEnemyInfo = [](Guerrier *enemy) -> void {
    if (enemy != nullptr)
    {
        std::cout << "##################\n"
                  << "Name : " << enemy->getName() << " / Equipe : " << enemy->getTeam()
                  << " / HP : " << enemy->getHp() << " / Attack : " << enemy->getCapAttack()
                  << " / Def : " << enemy->getCapDef() << "\n";
    }
    else
    {
        std::cout << "##################\n"
                  << "No enemy arround\n";
    }
};

void Game::start()
{
    int pm = 4;
    while (running)
    {
        system("clear");
        printInfo(getCurrent(), pm);
        printEnemyInfo(carte->CheckEnemy(getCurrent()));
        carte->printMap();
        if (step())
        {
            pm--;
            if (pm == 0)
            {
                pm = 4;
                increment();
            }
        }
        isGameOver();
    }

    system("clear");
    printInfo(getCurrent(), pm);
    printEnemyInfo(carte->CheckEnemy(getCurrent()));
    carte->printMap();
    std::cout << "\n" + getWinner() + "\n";
}

void Game::isGameOver()
{
    running = teamList.size() > 1;
}

std::string Game::getWinner()
{
    if (running)
        return "No Winner";
    return teamList.begin()->first + " Wins";
}

std::vector<std::vector<char>> Game::getMap()
{
    return carte->getMap();
}

int Game::getHeight()
{
    return carte->getHeight();
}

int Game::getWidth()
{
    return carte->getWidth();
}

Guerrier* Game::getEnemy()
{
    return carte->CheckEnemy(getCurrent());
}

