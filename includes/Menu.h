#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

class Menu
{
public:
    Menu(std::vector<std::string> items, sf::Font font);
    int select(sf::RenderWindow *window);

private:
    void setSelected(int i);
    std::vector<sf::Text *> _items = {};
    float scale = 50.f;
    int selected = 0;
};

#endif