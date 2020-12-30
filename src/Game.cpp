#include "../includes/Game.h"
#include "../includes/Carte.h"
#include "../includes/Team.h"

// const Game::OS Game::MY_OS = Windows;
const Game::OS Game::MY_OS = Linux;

Game::Game(std::string file) : _file(file)
{
    carte = new Carte(_file, this);
}

void Game::deleteAll()
{
    delete carte;
    for (auto e : teamList)
        delete e.second;
}

void Game::reset()
{
    deleteAll();
    this->currentTeam = 0;
    this->running = true;
    this->teamList = {};
    carte = new Carte(_file, this);
}

void Game::reset(std::string file)
{
    _file = file;
    reset();
}

Game::~Game()
{
    deleteAll();
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
    getCurrentTeam()->increment();
    currentTeam++;
    currentTeam = currentTeam % teamList.size();
    pm = Game::PM; // restore pm
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

void Game::isGameOver()
{
    if (getEmptyTeam() != teamList.end())
        teamList.erase(getEmptyTeam());
    running = teamList.size() > 1;
}

bool Game::isRunnig()
{
    return running;
};

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

Guerrier *Game::getEnemy()
{
    return carte->CheckEnemy(getCurrent());
}

void Game::decrementPM()
{
    pm--;
    if (pm <= 0)
        increment();
}

bool Game::step(char key)
{
    if (!running)
        return false;

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

// Les methodes et fonctions à partir de cette ligne ne sont utilisé que pour l'affichage dans le terminal linux

char getKey()
{
    char in;
    std::cin >> in;
    return in;
}

// 2 fonctions qui servent à afficher les infos à propos du guerrier
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

bool Game::step()
{
    return step(getKey());
}

void Game::start()
{
    int pm = 4;
    while (running)
    {
        if (MY_OS == Windows)
            system("cls");
        else
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
