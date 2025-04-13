#include "Panel.hpp"

Panel::Panel(const sf::Vector2f& size,
             const ResourceManager& resourceManager,
             GameCore& gameCore,
             const GameData& gameData,
             const sf::Vector2f& startPosition)
    : _resourceManager(resourceManager), 
    _gameCore(gameCore),
    _gameData(gameData),
    _flags({180.0f, 100.0f}, _resourceManager),
    _stopWatch({180.0f, 100.0f}, _resourceManager),
    _restart({100.0f, 60.0f}, _resourceManager, "Restart", [&](){ _gameCore.reset(); _stopWatch.reset(); })
{
    setSize(size);
    setPosition(startPosition);
    _restart.setPosition(_gameData.resetPosition());
    _flags.setPosition(_gameData.flagCounterPosition());
    _stopWatch.setPosition(_gameData.stopWatchPosition());
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


    