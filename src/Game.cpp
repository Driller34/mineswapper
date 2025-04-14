#include "Game.hpp"

Game::Game()
 : _gameData(), 
   _resourceManager("../resources"),
   _window(sf::VideoMode({conf::width, conf::height}), "Mineswapper"),
   _gameStateManager()
{
    _gameStateManager.push(std::make_unique<MenuState>(_gameStateManager, _resourceManager, _gameData));
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

    const sf::Vector2u size = _window.getSize();
   /*  if(size.x != _gameData.width() || size.y != _gameData.height())
    {
        _window.setSize({_gameData.width(), _gameData.height()});
        _window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(_gameData.width(), _gameData.height()))));
    } */
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

