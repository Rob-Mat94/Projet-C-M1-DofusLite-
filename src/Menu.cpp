#include "../includes/Menu.h"

Menu::Menu(std::vector<std::string> items, sf::Font font)
{
    int i = 5;
    for (std::string str : items)
    {
        sf::Text *text = new sf::Text(str, font);
        text->setPosition(scale, scale * i++);
        _items.push_back(text);
    }
}

int Menu::select(sf::RenderWindow *window)
{
    while (window->isOpen())
    {

        sf::Event event;
        while (window->pollEvent(event))
        {
            _items[selected]->setFillColor(sf::Color::Blue);
            window->clear();
            for (auto item : _items)
            {
                window->draw(*item);
            }
            window->display();
            if (event.type == sf::Event::Closed)
                window->close();
            if (event.type == sf::Event::KeyPressed)
                switch (event.key.code)
                {
                case sf::Keyboard::Z:
                    setSelected(-1);
                    break;
                case sf::Keyboard::S:
                    setSelected(1);
                    break;
                case sf::Keyboard::Enter:
                    return selected;
                default:
                    break;
                }
        }
    }
    return -1;
}

void Menu::setSelected(int i)
{
    selected += i;
    if ((size_t)selected >= _items.size())
        selected = _items.size() - 1;
    if ((size_t)selected < 0)
        selected = 0;
}