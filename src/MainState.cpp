#include "MainState.hpp"
#include <iostream>

MainState::MainState(const GameData& gameData,
                     const ResourceManager& resourceManager) 
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _panel(sf::Vector2f(_gameData.PanelWidth, _gameData.PanelHeight), _resourceManager, {0.0f, 0.0f}),
    _gameCore(_gameData, _resourceManager)
{
    _gameCore.setPosition(_gameData.startPosition);
}

void MainState::init()
{
    
}

void MainState::update()
{
}

void MainState::draw(sf::RenderWindow& window)
{
    window.draw(_panel);
    window.draw(_gameCore);
}

void MainState::onRightClick(const sf::Vector2i mousePosition)
{
   if(_gameCore.getLocalBounds().contains(sf::Vector2f(mousePosition))){ _gameCore.onRightClick(mousePosition); }
}

void MainState::onLeftClick(const sf::Vector2i mousePosition)
{
    if(_gameCore.getLocalBounds().contains(sf::Vector2f(mousePosition))){ _gameCore.onLeftClick(mousePosition); }
    if(_panel.getLocalBounds().contains(sf::Vector2f(mousePosition)))
    {
        _panel.onLeftClick(mousePosition);
    }
}