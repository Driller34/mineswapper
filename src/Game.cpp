#include "Game.hpp"

Game::Game()
 : _gameData(), 
   _resourceManager("../resources"),
   _window(sf::VideoMode({1000, 1000}), "Mineswapper"),
   _gameStateManager()
{
    _window.setSize({_gameData.width(), _gameData.height()});
    _window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(_gameData.width(), _gameData.height()))));
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

