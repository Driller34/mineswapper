#include "MainState.hpp"


MainState::MainState(const GameData& gameData,
                     const ResourceManager& resourceManager) 
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _gameCore(_gameData, _resourceManager),
    _container(sf::Vector2f(_gameData.panelWidth(), _gameData.panelHeight()))
    
{
    //_panel(sf::Vector2f(_gameData.panelWidth(), _gameData.panelHeight()), _resourceManager, _gameCore, _gameData, _gameData.panelPosition)
    _gameCore.setPosition(_gameData.startPosition());
    _container.setPosition(_gameData.panelPosition);

    _container.push(std::make_unique<Button>(
        sf::Vector2f(100.0f, 60.0f),
        _resourceManager,
        "Restart",
        _gameData.resetPosition(),
        [&]() { _gameCore.reset(); }
    ));

    _container.push(std::make_unique<StopWatch>(
        sf::Vector2f(180.0f, 100.0f),
        _gameData.stopWatchPosition(), 
        _resourceManager
    ));

    _container.push(std::make_unique<FlagCounter>(
        sf::Vector2f(180.0f, 100.0f),
        _gameData.flagCounterPosition(),
        _resourceManager,
        _gameCore
    ));
}

void MainState::init()
{
    
}

void MainState::update()
{
    _container.update();
}

void MainState::draw(sf::RenderWindow& window)
{
    window.draw(_container);
    window.draw(_gameCore);
}

void MainState::inputHandler(const sf::Event& event, 
                             sf::RenderWindow& window)
{
    if(const auto* mouseEvent = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if(mouseEvent->button == sf::Mouse::Button::Right)
        {
            onRightClick(sf::Mouse::getPosition(window));
        }
        if(mouseEvent->button == sf::Mouse::Button::Left)
        {
            onLeftClick(sf::Mouse::getPosition(window));
        }
    }
}

void MainState::onRightClick(const sf::Vector2i& mousePosition)
{
    _gameCore.onRightClick(mousePosition); 
}

void MainState::onLeftClick(const sf::Vector2i& mousePosition)
{
    _gameCore.onLeftClick(mousePosition);
    _container.onLeftClick(mousePosition);
}