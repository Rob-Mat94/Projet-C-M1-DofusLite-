#include "../includes/Gui.h"

using namespace sf;

Gui::Gui()
{
    initTextures();
    initWindow();
    initConfig();
}

Gui::~Gui()
{
    delete game;
    delete window;
};

void Gui::reset()
{
    if (game == nullptr)
        game = new Game(cartes[selected]);
    else
    {
        game->reset();
        initSize();
    }
}

void Gui::reset(std::string file)
{
    if (game == nullptr)
        game = new Game(file);
    else
        game->reset(file);
    initSize();
}

void Gui::initWindow()
{
    font.loadFromFile("res/yoster.ttf");
    window = new sf::RenderWindow(sf::VideoMode(width, height), "DofusLite");
    window->setPosition({0, 25});
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
    if (game != nullptr)
    {
        height = game->getHeight() * scale + infoBarHeight;
        width = game->getWidth() * scale;
    }
    if (window != nullptr)
        window->setSize(Vector2u(width, height));
}

void Gui::initConfig()
{
    std::ifstream config("res/.config", std::ios::in);
    if (config)
    {
        std::string line;
        while (getline(config, line))
        {
            int n = line.find(":");
            std::string first = line.substr(0, n),
                        second = line.substr(n + 1, line.size());
            names.push_back(first);
            cartes.push_back(second);
        }
    }
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
    std::vector<std::vector<char>> map = game->getMap();
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
    drawInformation(*game->getCurrent(), 0, height - infoBarHeight);
    if (game->getEnemy() != nullptr)
    {
        drawInformation(*game->getEnemy(), width / 3, height - infoBarHeight);
        drawCommandInformation(width / 2 + width / 6, height - infoBarHeight);
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
    std::string name = game->getCurrent()->getName();
    int x = game->getCurrent()->getPosition().getPosX() * scale;
    int y = game->getCurrent()->getPosition().getPosY() * scale;
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
    std::string str = "** " + game->getWinner() + " ** Press Escape to go to main menu, or R to restart !";
    sf::Text text(str, font, 15);
    sf::FloatRect bounds(text.getLocalBounds());

    RectangleShape shape({bounds.width + 10, bounds.height + 10});
    shape.setFillColor(Color::Black);

    // aggrandir la fenetre si le text ne rentre pas
    if (bounds.width + 10 > window->getSize().x)
        window->setSize({(unsigned int)bounds.width + 10, window->getSize().y});

    // Sert a centrer le text
    int x = (bounds.width - window->getSize().x) / 2 + bounds.left,
        y = (bounds.height - window->getSize().y) / 2 + bounds.top,
        x2 = (bounds.width - 10 - window->getSize().x) / 2 + bounds.left + 10,
        y2 = (bounds.height - 10 - window->getSize().y) / 2 + bounds.top + 10;

    text.setOrigin(x, y);
    shape.setOrigin(x2, y2);
    window->draw(shape);
    window->draw(text);
}

void Gui::drawTitle()
{
    Text title("DofusLite", font);
    const sf::FloatRect bounds(title.getLocalBounds());
    title.setOrigin((bounds.width - window->getSize().x) / 2 + bounds.left, 0);
    title.setPosition(0, scale);
    title.setFillColor(Color::Red);
    title.setOutlineThickness(2);
    title.setOutlineColor(Color::Green);
    title.setStyle(Text::Style::Underlined);
    window->draw(title);
}

auto Gui::getItems()
{
    std::vector<Text> items;
    int i = 150;
    for (auto str : names)
    {
        Text item(str, font, 25);
        item.setPosition(scale, i);
        items.push_back(item);
        i += 50;
    }

    Text quit("Quitter", font, 25);
    quit.setPosition(scale, i);
    items.push_back(quit);
    items[selected].setFillColor(Color::Green);
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
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect view(0, 0, window->getSize().x, window->getSize().y);
                window->setView(View(view));
            }
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
    selected = (selected + i);
    if (selected < 0)
        selected = cartes.size();
    if ((size_t)selected > cartes.size())
        selected = 0;
}

bool Gui::step()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect view(0, 0, window->getSize().x, window->getSize().y);
            window->setView(View(view));
        }
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
                return game->step('z');
            case sf::Keyboard::S:
                return game->step('s');
            case sf::Keyboard::Q:
                return game->step('q');
            case sf::Keyboard::D:
                return game->step('d');
            case sf::Keyboard::Y:
                return game->step('y');
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
        game->isGameOver();
        window->clear();
        drawMap();

        if (step())
            game->decrementPM();

        if (!game->isRunnig())
            drawWinner();

        window->display();
    }
}

void Gui::launch()
{
    displayMenu();
}