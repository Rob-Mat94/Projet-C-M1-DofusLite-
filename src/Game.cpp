#include "../includes/Game.h"
#include "../includes/Carte.h"
#include "../includes/Team.h"

// const Game::OS Game::MY_OS = Windows;
const Game::OS Game::MY_OS = Linux;

Game::Game(std::string file) : _file(file)
{
    _carte = new Carte(_file, this);
}

void Game::deleteAll()
{
    delete _carte;
    for (auto e : _teamList)
        delete e.second;
}

void Game::reset()
{
    deleteAll();
    this->_currentTeam = 0;
    this->_running = true;
    this->_teamList = {};
    _carte = new Carte(_file, this);
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
    for (auto it = _teamList.begin(); it != _teamList.end(); it++)
    {
        if (it->second->guerriersRestants() <= 0)
            return it;
    }
    return _teamList.end();
}

void Game::increment()
{
    getCurrentTeam()->increment();
    _currentTeam++;
    _currentTeam = _currentTeam % _teamList.size();
    _pm = Game::PM; // restore pm
}

Team *Game::getCurrentTeam()
{
    if (_teamList.empty())
        return nullptr;

    _currentTeam = _currentTeam % _teamList.size();
    auto it = _teamList.begin();
    std::advance(it, _currentTeam);

    return it->second;
}

void Game::addGuerrier(Guerrier *g)
{
    if (_teamList.find(g->getTeam()) == _teamList.end())
        _teamList[g->getTeam()] = new Team();
    _teamList[g->getTeam()]->addGuerrier(g);
}

void Game::removeGuerrier(Guerrier *g)
{
    _teamList[g->getTeam()]->removeGuerrier(g);
}

void Game::isGameOver()
{
    if (getEmptyTeam() != _teamList.end())
        _teamList.erase(getEmptyTeam());
    _running = _teamList.size() > 1;
}

bool Game::isRunnig() const
{
    return _running;
};

std::string Game::getWinner() const
{
    if (_running)
        return "No Winner";
    return _teamList.begin()->first + " Wins";
}

std::vector<std::vector<char>> Game::getMap() const
{
    return _carte->getMap();
}

int Game::getHeight() const
{
    return _carte->getHeight();
}

int Game::getWidth() const
{
    return _carte->getWidth();
}

Guerrier *Game::getEnemy()
{
    return _carte->checkEnemy(getCurrent());
}

void Game::decrementPM()
{

    _pm--;
    if (_pm <= 0)
        increment();
}

bool Game::step(char key)
{
    if (!_running)
        return false;

    switch (key)
    {
    case 'e':
        exit(0);
        break;
    case 'z':
        return getCurrent()->move(Up, _carte);
    case 's':
        return getCurrent()->move(Down, _carte);
    case 'q':
        return getCurrent()->move(Left, _carte);
    case 'd':
        return getCurrent()->move(Right, _carte);
    case 'y':
        if (getCurrent()->Attack(getEnemy(), _carte))
        {
            increment();
            return true;
        }
        else
            return false;
    }
    return false;
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
    while (_running)
    {
        if (MY_OS == Windows)
            system("cls");
        else
            system("clear");

        printInfo(getCurrent(), _pm);
        printEnemyInfo(getEnemy());
        _carte->printMap();
        if (step())
            decrementPM();
        isGameOver();
    }

    system("clear");
    printInfo(getCurrent(), _pm);
    printEnemyInfo(getEnemy());
    _carte->printMap();
    std::cout << "\n" + getWinner() + "\n";
}
