#include "Panel.hpp"
#include <iostream>

Panel::Panel(const sf::Vector2f& size,
             const ResourceManager& resourceManager,
             GameCore& gameCore,
             const sf::Vector2f& startPosition)
    : _resourceManager(resourceManager), 
    _gameCore(gameCore),
    _flags({180.0f, 100.0f}, _resourceManager),
    _stopWatch({180.0f, 100.0f}, _resourceManager),
    _restart({100.0f, 60.0f}, _resourceManager, "Restart", [&](){ _gameCore.init(); _stopWatch.restart(); })
{
    setSize(size);
    setPosition(startPosition);
    _restart.setPosition({40.0f, 20.0f});
    _flags.setPosition({150.0f, 20.0f});
    _stopWatch.setPosition({250.0f, 20.0f});
}

void Panel::update()
{
    _flags.setValue(_gameCore.countFlags());
    if(_gameCore.isGameRunning()){ _stopWatch.update(); }
}

void Panel::onLeftClick(const sf::Vector2i& mousePosition)
{
    if(!isClicked(mousePosition)){ return; }
    _restart.onLeftClick(mousePosition);
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
    target.draw(_stopWatch, states);
}


    