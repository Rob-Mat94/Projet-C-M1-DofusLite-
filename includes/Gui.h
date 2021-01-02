#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class Gui
{
public:
    Gui();
    Gui(const Gui &) = delete;
    Gui &operator=(const Gui &) = delete;
    virtual ~Gui();

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
    void initConfig();
    void reset();
    void reset(std::string file);

    Game *game = nullptr;
    sf::Font font;
    sf::RenderWindow *window = nullptr;
    std::map<char, sf::Texture> textures = {};
    std::vector<std::string> cartes = {}, names = {};
    int width = 500, height = 500;
    float scale = 45.f;
    float infoBarHeight = (1.3f * scale);
    int selected = 0;
};

#endif
