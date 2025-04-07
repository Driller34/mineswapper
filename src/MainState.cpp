#include "MainState.hpp"
#include <iostream>

MainState::MainState(const GameData& gameData,
                     const ResourceManager& resourceManager) 
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _gameCore(_gameData, _resourceManager),
    _panel(sf::Vector2f(_gameData.PanelWidth, _gameData.PanelHeight), _resourceManager, _gameCore, {0.0f, 0.0f})
{
    _gameCore.setPosition(_gameData.startPosition);
}

void MainState::init()
{
    
}

void MainState::update()
{
    _panel.update();
}

void MainState::draw(sf::RenderWindow& window)
{
    window.draw(_panel);
    window.draw(_gameCore);
}

void MainState::onRightClick(const sf::Vector2i mousePosition)
{
    _gameCore.onRightClick(mousePosition); 
}

void MainState::onLeftClick(const sf::Vector2i mousePosition)
{
    _gameCore.onLeftClick(mousePosition);
    _panel.onLeftClick(mousePosition);
}