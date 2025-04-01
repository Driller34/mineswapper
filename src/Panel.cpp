#include "Panel.hpp"

Panel::Panel(const sf::Vector2f size,
             const sf::Vector2f startPosition)
    : _size(size),
    _startPosition(startPosition),
    _restart({20.0f, 100.0f}, "Restart")
{
    _restart.setPosition({40.0f, 20.0f});
}

void Panel::draw(sf::RenderTarget& target, 
                 sf::RenderStates states) const
{
    sf::RectangleShape rec(_size);
    rec.setPosition(_startPosition);
    rec.setFillColor(sf::Color::Black);
    target.draw(rec, states);
    target.draw(_restart);
}


    