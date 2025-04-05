#include "Panel.hpp"
#include <iostream>

Panel::Panel(const sf::Vector2f size,
             const ResourceManager& resourceManager,
             GameCore& gameCore,
             const sf::Vector2f startPosition)
    : _resourceManager(resourceManager), 
    _gameCore(gameCore),
    _restart({100.0f, 60.0f}, _resourceManager, "Restart", [&](){ return _gameCore.init(); }),
    _flags({180.0f, 100.0f}, _resourceManager),
    _timer({180.0f, 100.0f}, _resourceManager),
    _clock()
{
    setSize(size);
    setPosition(startPosition);
    _restart.setPosition({40.0f, 20.0f});
    _flags.setPosition({150.0f, 20.0f});
    _timer.setPosition({350.0f, 20.0f});
}

void Panel::update()
{
    _flags.setValue(_gameCore.countFlags());
    if(_clock.getElapsedTime().asSeconds() >= 1.0f)
    {
        _timer.incrementValue();
        _clock.restart();
    }
}

void Panel::onRightClick(const sf::Vector2i mousePosition)
{
}

void Panel::onLeftClick(const sf::Vector2i mousePosition)
{
    if(_restart.getLocalBounds().contains(sf::Vector2f(mousePosition)))
    {
        _restart.onClick();
    }
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
    target.draw(_flags, states);
    target.draw(_timer, states);
}


    