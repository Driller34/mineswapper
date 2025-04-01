#include "Panel.hpp"

Panel::Panel(const sf::Vector2f size,
             const sf::Vector2f startPosition)
    : _restart({100.0f, 60.0f}, "Restart")
{
    setSize(size);
    setPosition(startPosition);
    _restart.setPosition({40.0f, 20.0f});
}

void Panel::onRightClick(const sf::Vector2i mousePosition)
{
    if(_restart.getLocalBounds().contains(sf::Vector2f(mousePosition)))
    {
        _restart.onClick();
    }
}

void Panel::onLeftClick(const sf::Vector2i mousePosition)
{

}

void Panel::draw(sf::RenderTarget& target, 
                 sf::RenderStates states) const
{
    states.transform *= getTransform();
    sf::RectangleShape rec(getSize());
    rec.setPosition(getPosition());
    rec.setFillColor(sf::Color::Black);
    target.draw(rec, states);
    target.draw(_restart, states);
}


    