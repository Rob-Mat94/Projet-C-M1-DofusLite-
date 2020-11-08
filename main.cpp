#include "includes/Carte.h"

int main()
{
    Carte c("carte1.txt");
    std::cout << "Appuyez sur 'e' pour quitter" << std::endl;
    while (true)
    {
        system("clear");
        c.printMap();
        char dir;
        std::cin >> dir;
        switch (dir)
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
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}