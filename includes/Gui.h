#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class Gui
{
public:
    Gui();
    virtual ~Gui();
    Gui(std::string file);

    void launch();

private:
    void drawInformation(const Guerrier &g, int x, int y);
    void drawCommandInformation(int x, int y);
    void drawStat(int x, int y, char stat);
    void drawText(std::string str, int x, int y);
    void drawSprite(int x, int y, char c);
    void drawMapBackground();
    void drawMap();
    void drawWinner();
    void drawName();
    void drawMenu();

    void drawTitle();
    void displayMenu();
    auto getItems();
    void setSelected(int i);
    void start();
    bool step();

    void initSize();
    void initTextures();
    void initWindow();
    void reset();
    void reset(std::string file);

    Game game;
    sf::Font font;
    sf::RenderWindow *window;
    std::map<char, sf::Texture> textures = {};
    std::vector<sf::String> cartes = {"carte1.txt", "carte1.txt", "carte1.txt"};
    int width, height;
    float scale = 50.f;
    float infoBarHeight = (1.3f * scale);
    int selected = 0;
};

#endif