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
    void drawInformation(const Guerrier &g, int x, int y) const;
    void drawCommandInformation(int x, int y) const;
    void drawStat(int x, int y, char stat) const;
    void drawText(std::string str, int x, int y) const;
    void drawSprite(int x, int y, char c) const;
    void drawMapBackground() const;
    void drawMap() const;
    void drawWinner() const;
    void drawName() const;
    void drawMenu() const;

    void drawTitle() const;
    void displayMenu();
    auto getItems() const;
    void setSelected(int i);
    void start();
    bool step();

    void initSize();
    void initTextures();
    void initWindow();
    void initConfig();
    void reset();
    void reset(std::string file);

    Game *_game = nullptr;
    sf::Font _font;
    sf::RenderWindow *_window = nullptr;
    std::map<char, sf::Texture> _textures = {};
    std::vector<std::string> _mapFiles = {}, _mapNames = {};
    int _width = 500, _height = 500;
    float _scale = 45.f;
    float _infoBarHeight = (1.3f * _scale);
    int _selected = 0;
};

#endif
