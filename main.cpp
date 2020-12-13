#include "includes/Gui.h"

int main()
{
    Gui gui;
    gui.launch();
    return 0;
}

// #include "includes/Game.h"
// #include "includes/terminalSetting.h"

// int main()
// {
//     Game game = Game("carte1.txt");
//     initSettings();
//     game.start();
//     restoreSettings();
//     return 0;
// }

// #include "includes/Carte.h"
// #include "includes/terminalSetting.h"

// const int PM = 4;
// /* déterminer l'équipe courante qui joue */
// auto getTeam = [](int &index) -> auto
// {
//     if (index % 2 == 0)
//         return Carte::getTeam_2();
//     return Carte::getTeam_1();
// };

// auto printInfo = [](int &team_index, int &index_g, int &pm) -> void {
//     std::cout << "Appuyez sur 'e' pour quitter, z,q,s,d pour bouger" << std::endl;
//     /* Information sur le guerrier courant */
//     std::cout << getTeam(team_index)[index_g]->getName()
//               << ": HP -> "
//               << getTeam(team_index)[index_g]->getHp()
//               << ": PM -> "
//               << pm
//               << ": Dammage -> " << getTeam(team_index)[index_g]->getCapAttack()
//               << ": Defense -> " << getTeam(team_index)[index_g]->getCapDef()
//               << ": Team -> " << getTeam(team_index)[index_g]->getTeam()
//               << "\n";
// };

// auto printEnemyInfo = [](Guerrier *enemy) -> void {
//     if (enemy != nullptr)
//     {
//         std::cout << "##################\n"
//                   << "Name : " << enemy->getName() << " / Equipe : " << enemy->getTeam()
//                   << " / HP : " << enemy->getHp()
//                   << " / (Attack : " << enemy->getCapAttack() << " / Def : " << enemy->getCapDef()
//                   << ")\n##################\n"
//                   << "ATTAQUER ? (press \"Y\")\n";
//     }
// };

// int tour_g = PM;

// int main()
// {
//     Carte c("carte1.txt");
//     bool exit = false;

//     auto index_g = 0;
//     int team_index = 1;

//     Guerrier *enemy = nullptr;
//     const int team_size = getTeam(index_g).size();

//     auto PassTour = [](int &team_index, int &index, const int &size) -> void {
//         if (team_index % 2 == 0)
//             index++;
//         team_index++;
//         if (index == size)
//             index = 0;
//     };

//     initSettings();
//     while (!exit)
//     {
//         //if (system("clear") == -1)
//         //    std::cerr << "Erreur";

//         /* information sur le guerrier actuel */
//         printInfo(team_index, index_g, tour_g);
//         /* information sur un enemy proche */
//         printEnemyInfo(enemy);

//         c.printMap();
//         switch (getKey())
//         {
//         case 'y':
//             if (enemy != nullptr)
//             {
//                 getTeam(team_index)[index_g]->Attack(enemy, c);
//                 // PassTour(team_index, index_g, team_size);
//                 enemy = nullptr;
//             }
//             break;
//         case 'z':
//             if (getTeam(team_index)[index_g]->move(Up, c))
//                 tour_g--;
//             // check enemy
//             enemy = c.CheckEnemy(getTeam(team_index)[index_g]);
//             break;
//         case 's':
//             if (getTeam(team_index)[index_g]->move(Down, c))
//                 tour_g--;
//             // check enemy
//             enemy = c.CheckEnemy(getTeam(team_index)[index_g]);

//             break;
//         case 'q':
//             if (getTeam(team_index)[index_g]->move(Left, c))
//                 tour_g--;
//             // check enemy
//             enemy = c.CheckEnemy(getTeam(team_index)[index_g]);
//             break;
//         case 'd':
//             if (getTeam(team_index)[index_g]->move(Right, c))
//                 tour_g--;
//             // check enemy
//             enemy = c.CheckEnemy(getTeam(team_index)[index_g]);

//             break;
//         case 'e':
//             exit = true;
//             break;
//         /* passe le tour au membre suivant de l'autre équipe */
//         case 't':
//             PassTour(team_index, index_g, team_size);
//             break;
//         default:
//             break;
//         }

//         if (tour_g == 0)
//         {
//             PassTour(team_index, index_g, team_size);
//             tour_g = PM;
//         }
//     }

//     restoreSettings();
//     return 0;
// }