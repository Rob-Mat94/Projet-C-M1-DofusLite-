#include "../includes/Gui.h"

using namespace sf;

Gui::Gui() : game("carte1.txt")
{
    initTextures();
    initWindow();
}

Gui::Gui(std::string file) : game(file)
{
    initTextures();
    initWindow();
}

Gui::~Gui()
{
    delete window;
};

void Gui::reset()
{
    game.reset();
    initSize();
}

void Gui::reset(std::string file)
{
    game.reset(file);
    initSize();
}

void Gui::initWindow()
{
    font.loadFromFile("res/yoster.ttf");
    initSize();
    this->window = new sf::RenderWindow(sf::VideoMode(width, height + infoBarHeight), "DofusLite");
}

void Gui::initTextures()
{
    textures['G'].loadFromFile("res/team1.png");
    textures['g'].loadFromFile("res/team2.png");
    textures['p'].loadFromFile("res/potion.png");
    textures['A'].loadFromFile("res/armor.png");
    textures['S'].loadFromFile("res/sword.png");
    textures['M'].loadFromFile("res/map.jpg");
    textures['*'].loadFromFile("res/wall.jpg");

    for (auto t : textures)
        t.second.setSmooth(true);
}

void Gui::initSize()
{
    this->height = game.getHeight() * scale;
    this->width = game.getWidth() * scale;
}

void Gui::drawSprite(int x, int y, char c)
{
    Sprite sprite;
    sprite.setTexture(textures[c]);
    sprite.scale((scale / textures[c].getSize().x), (scale / textures[c].getSize().y));
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
            if (std::string("GASg*").find(map[y][x]) < 5)
            {
                drawSprite(x, y, map[y][x]);
            }
            else if (map[y][x] != ' ')
            {
                drawSprite(x, y, 'p');
                drawStat(x, y, map[y][x]);
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

void Gui::drawMapBackground()
{
    Sprite s;
    s.setTexture(textures['M']);
    s.scale(2, 2);
    window->draw(s);
}

void Gui::drawText(std::string str, int x, int y)
{
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
    std::string str = "\n\t*" + game.getWinner() + "*\tPress Escape to go to main menu, or R to restart !";
    drawText(str, 0, y);
}

void Gui::drawTitle()
{
    Text title("DofusLite", font);
    title.setPosition(scale * 3, scale * 2);
    window->draw(title);
}

auto Gui::getItems()
{
    std::vector<Text> items;
    int i = 5;
    for (auto str : cartes)
    {
        Text item(str, font);
        item.setPosition(scale, i * scale);
        items.push_back(item);
        i++;
    }

    Text quit("Quit", font);
    quit.setPosition(scale, scale * i);
    items.push_back(quit);
    items[selected].setFillColor(Color::Blue);
    return items;
}

void Gui::drawMenu()
{
    window->clear();
    drawMapBackground();
    drawTitle();
    for (auto item : getItems())
        window->draw(item);
    window->display();
}

void Gui::displayMenu()
{
    while (window->isOpen())
    {
        drawMenu();
        Event event;
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
                    setSelected(-1);
                    break;
                case sf::Keyboard::S:
                    setSelected(1);
                    break;
                case sf::Keyboard::Enter:
                    if ((size_t)selected < cartes.size())
                    {
                        reset(cartes[selected]);
                        start();
                    }
                    else
                        window->close();
                    break;
                default:
                    break;
                }
        }
    }
}

void Gui::setSelected(int i)
{
    selected = (selected + i) % (cartes.size() + 1);
}

bool Gui::step()
{
    game.isGameOver();
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::KeyPressed)
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                displayMenu();
                break;
            case sf::Keyboard::R:
                reset();
                start();
                break;
            case sf::Keyboard::Z:
                return game.step('z');
            case sf::Keyboard::S:
                return game.step('s');
            case sf::Keyboard::Q:
                return game.step('q');
            case sf::Keyboard::D:
                return game.step('d');
            case sf::Keyboard::Y:
                return game.step('y');
            default:
                return false;
            }
    }
    return false;
}

void Gui::start()
{
    while (window->isOpen())
    {
        window->clear();
        drawMap();

        if (step())
            game.decrementPM();

        if (!game.isRunnig())
            drawWinner();

        window->display();
    }
}

void Gui::launch()
{
    displayMenu();
}