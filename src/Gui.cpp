#include "../includes/Gui.h"

using namespace sf;

std::map<char, sf::Color> Gui::colors = {
    {'g', sf::Color::Red},
    {'G', sf::Color::Yellow},
    {'A', sf::Color::Magenta},
    {'S', sf::Color::Cyan},
    {'*', sf::Color::Blue},
    {'p', sf::Color::Green},
};

Gui::Gui() : game("carte1.txt")
{
    textures['G'].loadFromFile("res/team1.png");
    textures['g'].loadFromFile("res/team2.png");
    textures['p'].loadFromFile("res/potion.png");
    textures['A'].loadFromFile("res/armor.png");
    textures['S'].loadFromFile("res/sword.png");
}

Gui::Gui(std::string file) : game(file) {}

void Gui::initWindow()
{
    this->thickness = -2;
    this->scale = 50;
    this->height = game.getHeight() * scale;
    this->width = game.getWidth() * scale;
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), "DofusLite");
}

void Gui::drawMap()
{
    std::vector<std::vector<char>> map = game.getMap();
    for (std::size_t y = 0; y < map.size(); y++)
    {
        for (std::size_t x = 0; x < map[y].size(); x++)
        {
            if (map[y][x] == '*')
                drawObstacle(x, y);
            else
                drawSprite(x, y, map[y][x]);
            switch (map[y][x])
            {
            case 'g':
                drawSprite(x, y, 'g');
                break;
            case 'G':
                drawSprite(x, y, 'G');
                break;
            case 'A':
                drawSprite(x, y, 'A');
                break;
            case 'S':
                drawSprite(x, y, 'S');
                break;
            case '*':
                drawObstacle(x, y);
                break;
            case ' ':
                break;
            default:
                drawSprite(x, y, 'p');
                break;
            }
        }
    }
}

void Gui::drawSprite(int x, int y, char c)
{
    Texture texture = textures[c];
    texture.setSmooth(true);
    Sprite sprite;
    sprite.setTexture(texture);
    sprite.scale((scale / texture.getSize().x), (scale / texture.getSize().y));
    sprite.setPosition(scale * x, scale * y);
    window->draw(sprite);
}

void Gui::drawRect(int x, int y, sf::Color col)
{
    RectangleShape shape(Vector2f(scale, scale));
    shape.setOutlineThickness(thickness);
    shape.setOutlineColor(col);
    shape.setFillColor(Color::Black);
    shape.setPosition(scale * x, scale * y);
    window->draw(shape);
}

void Gui::drawGuerrier(int x, int y, char team)
{
    drawRect(x, y, colors[team]);
}

void Gui::drawObstacle(int x, int y)
{
    drawRect(x, y, colors['*']);
}

void Gui::drawPotion(int x, int y)
{
    drawRect(x, y, colors['p']);
}

void Gui::drawArmor(int x, int y)
{
    drawRect(x, y, colors['A']);
}

void Gui::drawSword(int x, int y)
{
    drawRect(x, y, colors['S']);
}

void Gui::launch()
{
    int pm = 4;
    initWindow();
    while (window->isOpen() && game.isRunnig())
    {
        char key = ' ';
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    window->close();
                    break;
                case sf::Keyboard::Z:
                    key = 'z';
                    break;
                case sf::Keyboard::S:
                    key = 's';
                    break;
                case sf::Keyboard::Q:
                    key = 'q';
                    break;
                case sf::Keyboard::D:
                    key = 'd';
                    break;
                case sf::Keyboard::Y:
                    key = 'y';
                    break;
                default:
                    break;
                }
        }

        if (game.step(key))
        {
            pm--;
            if (pm == 0)
            {
                pm = 4;
                game.increment();
            }
        }
        game.isGameOver();

        window->clear();
        drawMap();
        window->display();
    }
}