#include "MainState.hpp"


MainState::MainState(const GameData& gameData,
                     const ResourceManager& resourceManager) 
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _gameCore(_gameData, _resourceManager),
    _panel(sf::Vector2f(_gameData.PanelWidth, _gameData.PanelHeight), _resourceManager, _gameCore, _gameData, _gameData.panelPosition)
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
    _panel.onLeftClick(mousePosition);
}