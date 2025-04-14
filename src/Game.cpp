#include "Game.hpp"

Game::Game()
 : _resourceManager("../resources"),
   _window(sf::VideoMode({conf::width, conf::height}), "Mineswapper", sf::Style::Titlebar),
   _windowService(_window),
   _gameStateManager()
{
    _gameStateManager.push(std::make_unique<MenuState>(_gameStateManager, _resourceManager, _windowService));
}

void Game::run()
{
    while(_window.isOpen())
    {
        if(_gameStateManager.empty()){ _window.close(); }
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

