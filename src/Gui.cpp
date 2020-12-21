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
    textures['M'].loadFromFile("res/map.jpg");
    textures['*'].loadFromFile("res/wall.jpg");
    initWindow();
}

Gui::Gui(std::string file) : game(file)
{
    textures['G'].loadFromFile("res/team1.png");
    textures['g'].loadFromFile("res/team2.png");
    textures['p'].loadFromFile("res/potion.png");
    textures['A'].loadFromFile("res/armor.png");
    textures['S'].loadFromFile("res/sword.png");
    textures['M'].loadFromFile("res/map.jpg");
    textures['*'].loadFromFile("res/wall.jpg");
    initWindow();
}

void Gui::reset()
{
    window->close();
    delete window;
    game.reset();
    initWindow();
}

void Gui::initWindow()
{
    this->thickness = -2;
    this->scale = 50;
    this->height = game.getHeight() * scale;
    this->width = game.getWidth() * scale;
    this->infoBarHeight = width / 8;
    this->window = new sf::RenderWindow(sf::VideoMode(width, height + infoBarHeight), "DofusLite");
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

void Gui::drawMap()
{
    drawMapBackground();
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
                drawSprite(x, y, '*');
                break;
            case ' ':
                break;
            default:
                drawSprite(x, y, 'p');
                drawStat(x, y, map[y][x]);
                break;
            }
        }
    }

    drawName();
    drawInformation(*game.getCurrent(), 0, height + infoBarHeight / 15);
    if (game.getEnemy() != nullptr)
    {
        drawInformation(*game.getEnemy(), width / 3, height + infoBarHeight / 15);
        drawCommandInformation(width / 2 + width / 6, height + infoBarHeight / 15);
    }
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

void Gui::drawObstacle(int x, int y)
{
    drawRect(x, y, colors['*']);
}

void Gui::drawMapBackground()
{
    Texture mappng = textures['M'];
    mappng.setSmooth(true);
    Sprite s;
    s.setTexture(mappng);
    window->draw(s);
}

void Gui::drawText(std::string str, int x, int y)
{
    Font font;
    font.loadFromFile("res/yoster.ttf");
    sf::Text text(str, font, 12);
    text.setPosition(x, y);
    window->draw(text);
}

void Gui::drawInformation(const Guerrier &g, int x, int y)
{
    /* Name / Hp / Attack / Def*/
    std::string info = "#Name : " + g.getName() + "\n" + std::to_string(g.getHp()) + " HP\n" + std::to_string(g.getCapAttack()) + " Attack damage\n" + std::to_string(g.getCapDef()) + " Defense";
    drawText(info, x, y);
}

void Gui::drawName()
{
    std::string name = game.getCurrent()->getName();
    int x = game.getCurrent()->getPosition().getPosX() * scale;
    int y = game.getCurrent()->getPosition().getPosY() * scale;
    drawText(name, x, y);
}

void Gui::drawStat(int x, int y, char stat)
{
    drawText({stat}, x * scale, y * scale - 12);
}

void Gui::drawCommandInformation(int x, int y)
{
    drawText("Press Y to attack", x, y);
}

void Gui::drawWinner()
{
    int y = (game.getHeight() * scale) / 2;

    RectangleShape shape(Vector2f(game.getWidth() * scale, scale));
    shape.setFillColor(Color::Black);
    shape.setPosition(0, y);
    window->draw(shape);
    std::string str = "\n\t**" + game.getWinner() + "**\tPress Escape or close to leave or R to restart !";
    drawText(str, 0, y);
}

void Gui::launch()
{
    int pm = 4;
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

    while (window->isOpen())
    {
        window->clear();
        drawMap();
        drawWinner();
        window->display();

        sf::Event event;
        window->pollEvent(event);
        if (event.type == sf::Event::Closed)
            window->close();
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            window->close();
        if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::R))
        {
            reset();
            launch();
        }
    }
}