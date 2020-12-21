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
    void reset();
    void drawMap();
    void launch();

private:
    void drawObstacle(int x, int y);
    void drawMapBackground();
    void drawInformation(const Guerrier &g, int x, int y);
    void drawCommandInformation(int x, int y);
    void drawName();
    void drawStat(int x, int y, char stat);
    void drawText(std::string str, int x, int y);
    void drawWinner();
    /*
    void drawGuerrier(int x, int y, char team);
    void drawPotion(int x, int y);
    void drawArmor(int x, int y);
    void drawSword(int x, int y);
    */
    void drawRect(int x, int y, sf::Color col);

    void drawSprite(int x, int y, char c);

    static std::map<char, sf::Color> colors;
    std::map<char, sf::Texture> textures = {};

    Game game;
    sf::RenderWindow *window;
    float width, height, scale, thickness, infoBarHeight;
};

#endif