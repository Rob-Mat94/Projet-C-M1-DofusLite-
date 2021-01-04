#include "../includes/Gui.h"

using namespace sf;

Gui::Gui()
{
    initTextures();
    initWindow();
    initMusic();
    initConfig();
}

Gui::~Gui()
{
    delete _game;
    delete _window;
};

void Gui::reset()
{
    if (_game == nullptr)
        _game = new Game(_mapFiles[_selected]);
    else
    {
        _game->reset();
        initSize();
    }
}

void Gui::reset(std::string file)
{
    if (_game == nullptr)
        _game = new Game(file);
    else
        _game->reset(file);
    initSize();
}

void Gui::initWindow()
{
    _font.loadFromFile("res/yoster.ttf");
    _window = new sf::RenderWindow(sf::VideoMode(_width, _height), "DofusLite");
    _window->setPosition({0, 25});
}

void Gui::initTextures()
{
    _textures['G'].loadFromFile("res/team1.png");
    _textures['g'].loadFromFile("res/team2.png");
    _textures['p'].loadFromFile("res/potion.png");
    _textures['A'].loadFromFile("res/armor.png");
    _textures['S'].loadFromFile("res/sword.png");
    _textures['M'].loadFromFile("res/map.jpg");
    _textures['*'].loadFromFile("res/wall.jpg");

    for (auto t : _textures)
        t.second.setSmooth(true);
}

void Gui::initMusic()
{
    if (!music.openFromFile("res/song.ogg"))
        std::cout << "le fichier song.ogg est introuvable)";
}

void Gui::initSize()
{
    if (_game != nullptr)
    {
        _height = _game->getHeight() * _scale + _infoBarHeight;
        _width = _game->getWidth() * _scale;
    }
    if (_window != nullptr)
        _window->setSize(Vector2u(_width, _height));
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
            _mapNames.push_back(first);
            _mapFiles.push_back(second);
        }
    }
}

void Gui::drawSprite(int x, int y, char c) const
{
    Sprite sprite;
    sprite.setTexture(_textures.at(c));
    sprite.scale((_scale / _textures.at(c).getSize().x), (_scale / _textures.at(c).getSize().y));
    sprite.setPosition(_scale * x, _scale * y);

    _window->draw(sprite);
}

void Gui::drawMap() const
{
    drawMapBackground();
    std::vector<std::vector<char>> map = _game->getMap();
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
    drawInformation(*_game->getCurrent(), 0, _height - _infoBarHeight);
    if (_game->getEnemy() != nullptr)
    {
        drawInformation(*_game->getEnemy(), _width / 3, _height - _infoBarHeight);
        drawCommandInformation(_width / 2 + _width / 6, _height - _infoBarHeight);
    }
}

void Gui::drawMapBackground() const
{
    Sprite s;
    s.setTexture(_textures.at('M'));
    float x1 = (float)_window->getSize().x,
          y1 = (float)_window->getSize().y,
          x2 = (float)_textures.at('M').getSize().x,
          y2 = (float)_textures.at('M').getSize().y;
    s.scale(x1 / x2, y1 / y2);
    _window->draw(s);
}

void Gui::drawText(std::string str, int x, int y) const
{
    sf::Text text(str, _font, 12);
    text.setPosition(x, y);
    _window->draw(text);
}

void Gui::drawInformation(const Guerrier &g, int x, int y) const
{
    /* Name / Hp / Attack / Def*/
    std::string info = "#Name : " + g.getName() + "\n" + std::to_string(g.getHp()) + " HP\n" + std::to_string(g.getCapAttack()) + " Attack damage\n" + std::to_string(g.getCapDef()) + " Defense";
    drawText(info, x, y);
}

void Gui::drawName() const
{
    std::string name = _game->getCurrent()->getName();
    int x = _game->getCurrent()->getPosition().getPosX() * _scale;
    int y = _game->getCurrent()->getPosition().getPosY() * _scale;
    drawText(name, x, y);
}

void Gui::drawStat(int x, int y, char stat) const
{
    drawText({stat, '0'}, x * _scale, y * _scale - 12);
}

void Gui::drawCommandInformation(int x, int y) const
{
    drawText("Press Y to attack", x, y);
}

void Gui::drawWinner() const
{
    std::string str = "** " + _game->getWinner() + " ** Press Escape to go to main menu, or R to restart !";
    sf::Text text(str, _font, 15);
    sf::FloatRect bounds(text.getLocalBounds());

    RectangleShape shape({bounds.width + 10, bounds.height + 10});
    shape.setFillColor(Color::Black);

    // aggrandir la fenetre si le text ne rentre pas
    if (bounds.width + 10 > _window->getSize().x)
        _window->setSize({(unsigned int)bounds.width + 10, _window->getSize().y});

    // Sert a centrer le text
    int x = (bounds.width - _window->getSize().x) / 2 + bounds.left,
        y = (bounds.height - _window->getSize().y) / 2 + bounds.top,
        x2 = (bounds.width - 10 - _window->getSize().x) / 2 + bounds.left + 10,
        y2 = (bounds.height - 10 - _window->getSize().y) / 2 + bounds.top + 10;

    text.setOrigin(x, y);
    shape.setOrigin(x2, y2);
    _window->draw(shape);
    _window->draw(text);
}

void Gui::drawTitle() const
{
    Text title("DofusLite", _font);
    const sf::FloatRect bounds(title.getLocalBounds());
    title.setOrigin((bounds.width - _window->getSize().x) / 2 + bounds.left, 0);
    title.setPosition(0, _scale);
    title.setFillColor(Color::Red);
    title.setOutlineThickness(2);
    title.setOutlineColor(Color::Green);
    title.setStyle(Text::Style::Underlined);
    _window->draw(title);
}

auto Gui::getItems() const
{
    std::vector<Text> items;
    int i = 150;
    for (auto str : _mapNames)
    {
        Text item(str, _font, 25);
        item.setPosition(_scale, i);
        items.push_back(item);
        i += 50;
    }

    Text quit("Quitter", _font, 25);
    quit.setPosition(_scale, i);
    items.push_back(quit);
    items[_selected].setFillColor(Color::Green);
    return items;
}

void Gui::drawMenu() const
{
    _window->clear();
    drawMapBackground();
    drawTitle();
    for (auto item : getItems())
        _window->draw(item);
    _window->display();
}

void Gui::displayMenu()
{
    while (_window->isOpen())
    {
        drawMenu();
        Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window->close();
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect view(0, 0, _window->getSize().x, _window->getSize().y);
                _window->setView(View(view));
            }
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    _window->close();
                    break;
                case sf::Keyboard::Z:
                    setSelected(-1);
                    break;
                case sf::Keyboard::S:
                    setSelected(1);
                    break;
                case sf::Keyboard::Enter:
                    if ((size_t)_selected < _mapFiles.size())
                    {
                        reset(_mapFiles[_selected]);
                        start();
                    }
                    else
                        _window->close();
                    break;
                default:
                    break;
                }
        }
    }
}

void Gui::setSelected(int i)
{
    _selected = (_selected + i);
    if (_selected < 0)
        _selected = _mapFiles.size();
    if ((size_t)_selected > _mapFiles.size())
        _selected = 0;
}

void Gui::setMusicPlayPause()
{
    switch (music.getStatus())
    {
    case sf::Music::Playing:
        music.pause();
    default:
        music.play();
        break;
    }
}

bool Gui::step()
{
    // recommencer la musique si elle s'arrête
    if (music.getStatus() == Music::Status::Stopped)
        music.play();

    sf::Event event;
    while (_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _window->close();
        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect view(0, 0, _window->getSize().x, _window->getSize().y);
            _window->setView(View(view));
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
                return _game->step('z');
            case sf::Keyboard::S:
                return _game->step('s');
            case sf::Keyboard::Q:
                return _game->step('q');
            case sf::Keyboard::D:
                return _game->step('d');
            case sf::Keyboard::Y:
                return _game->step('y');
            case sf::Keyboard::P:
                setMusicPlayPause();
                break;
            default:
                return false;
            }
    }
    return false;
}

void Gui::start()
{
    while (_window->isOpen())
    {
        _game->isGameOver();
        _window->clear();
        drawMap();

        if (step())
            _game->decrementPM();

        if (!_game->isRunnig())
            drawWinner();

        _window->display();
    }
}

void Gui::launch()
{
    music.play();
    displayMenu();
}