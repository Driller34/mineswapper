#include "Game.hpp"

Game::Game()
 : _gameData(), 
   _resourceManager("../resources"),
   _window(sf::VideoMode({_gameData.width, _gameData.height}), "Mineswapper"),
   _mainState(_gameData, _resourceManager)
{
}

void Game::run()
{
    while(_window.isOpen())
    {
        update();
        processEvent();
        render();   
    }
}

void Game::update()
{
    _mainState.update();
}

void Game::render()
{
    _window.clear();
    _mainState.draw(_window);
    _window.display();
}

void Game::processEvent()
{
    while(const std::optional<sf::Event> event = _window.pollEvent())
    {
        if(event->is<sf::Event::Closed>()){ _window.close(); }
        if(const auto* mouseEvent = event->getIf<sf::Event::MouseButtonReleased>())
        {
            if(mouseEvent->button == sf::Mouse::Button::Right)
            {
                _mainState.onRightClick(sf::Mouse::getPosition(_window));
            }
            if(mouseEvent->button == sf::Mouse::Button::Left)
            {
                _mainState.onLeftClick(sf::Mouse::getPosition(_window));
            }
        }
    }
}

