#include "includes/Carte.h"

/* déterminer l'équipe courante qui joue */
auto getTeam = [] (int &index) -> auto 
{
    if(index % 2 == 0)
        return Carte::getTeam_2();
    return Carte::getTeam_1();    
};

auto printInfo = [] (int &team_index, int &index_g) -> void
{
    std::cout << "Appuyez sur 'e' pour quitter, z,q,s,d pour bouger" << std::endl;
    /* Information sur le guerrier courant */
    std::cout << getTeam(team_index)[index_g]->getName() << ": hp -> " <<  getTeam(team_index)[index_g]->getHp() << " Team : " <<
         getTeam(team_index)[index_g]->getTeam() << "\n";
};

auto printEnemyInfo = [](Guerrier* enemy) -> void
{
    if(enemy != nullptr)
        {
            std::cout << "##################\n" << "Name : " << enemy->getName() << " / Equipe : " << enemy->getTeam()
            << " / (Attack : " << enemy->getCapAttack() << " / Def : " << enemy->getCapDef() <<")\n##################\n"; 
        }
};

int main()
{
    Carte c("carte1.txt");
    bool exit = false;

    auto index_g = 0;
    int team_index = 1;
     
    Guerrier* enemy = nullptr;
    const int team_size = getTeam(index_g).size();


    while (!exit)
    {
        if(system("clear") == -1)std::cerr << "Erreur";
        
        /* information sur le guerrier actuel */
        printInfo(team_index,index_g);
        /* information sur un enemy proche */
        printEnemyInfo(enemy);
        
        c.printMap();
        std::string dir;
        std::cin >> dir;
        switch (dir.at(0))
        {
        case 'z':
            getTeam(team_index)[index_g]->move(Up, c);
            // check enemy
            enemy = c.CheckEnemy(getTeam(team_index)[index_g]);
            break;
        case 's':
            getTeam(team_index)[index_g]->move(Down, c);
             // check enemy
            enemy = c.CheckEnemy(getTeam(team_index)[index_g]);
            break;
        case 'q':
            getTeam(team_index)[index_g]->move(Left, c);
             // check enemy
            enemy = c.CheckEnemy(getTeam(team_index)[index_g]);
            break;
        case 'd':
            getTeam(team_index)[index_g]->move(Right, c);
             // check enemy
            enemy = c.CheckEnemy(getTeam(team_index)[index_g]);
            break;
        case 'e':
            exit = true;
            break;
        /* passe le tour au membre suivant de l'autre équipe */
        case 't':
            if(team_index % 2 == 0)
                index_g++;
            team_index++;
            if(index_g == team_size)
                index_g = 0;           
            break;
        default:
            break;
        }
    }
    return 0;
}