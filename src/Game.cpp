#include "Game.hpp"

Game::Game()
 : _gameData(), 
   _resourceManager("../resources"),
   _window(sf::VideoMode({_gameData.width, _gameData.height}), "Mineswapper"),
   _gameStateManager()
{
    _gameStateManager.push(std::make_unique<MainState>(_gameData, _resourceManager));
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
    _gameStateManager.update();
}

void Game::render()
{
    _window.clear();
    _gameStateManager.render(_window);
    _window.display();
}

void Game::processEvent()
{
    while(const std::optional<sf::Event> event = _window.pollEvent())
    {
        if(event->is<sf::Event::Closed>()){ _window.close(); }
        _gameStateManager.inputHandler(*event, _window);
    }
}

