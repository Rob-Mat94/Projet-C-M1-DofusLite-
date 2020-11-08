#include "includes/Carte.h"

int main()
{
    Carte c("carte1.txt");
    bool exit = false;
    while (!exit)
    {
        system("clear");
        std::cout << "Appuyez sur 'e' pour quitter, z,q,s,d pour bouger G" << std::endl;
        std::cout << "G: hp -> " << c.guerrier->getHp() << "\n";
        c.printMap();
        std::string dir;
        std::cin >> dir;
        switch (dir.at(0))
        {
        case 'z':
            c.guerrier->move(Up, c);
            break;
        case 's':
            c.guerrier->move(Down, c);
            break;
        case 'q':
            c.guerrier->move(Left, c);
            break;
        case 'd':
            c.guerrier->move(Right, c);
            break;
        case 'e':
            exit = true;
            break;
        default:
            break;
        }
    }
    return 0;
}