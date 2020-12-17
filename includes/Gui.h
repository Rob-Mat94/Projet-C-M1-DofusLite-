#ifndef GUI_H
#define GUI_H
#include <SFML/Graphics.hpp>
#include "Game.h"

class Gui
{
public:
    Gui();

    virtual ~Gui()
    {
        delete window;
    };

    Gui(std::string file);

    void initWindow();
    void drawMap();
    void launch();

private:
    void drawGuerrier(int x, int y, char team);
    void drawObstacle(int x, int y);
    void drawPotion(int x, int y);
    void drawArmor(int x, int y);
    void drawSword(int x, int y);
    void drawRect(int x, int y, sf::Color col);
    void drawSprite(int x, int y, char c);

    static std::map<char, sf::Color> colors;
    std::map<char, sf::Texture> textures = {};

    Game game;
    sf::RenderWindow *window;
    float width, height, scale, thickness;
};

#endif