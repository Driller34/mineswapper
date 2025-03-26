#include "Game.hpp"

Game::Game()
 : _gameData(), 
 _window(sf::VideoMode({_gameData.width, _gameData.height}), "Mineswapper"),
 _board(_gameData, {0.0f, 0.0f})
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

}

void Game::render()
{
    _window.clear();
    _window.draw(_board);
    _window.display();
}

void Game::processEvent()
{
    while(const std::optional event = _window.pollEvent())
    {
        if(event->is<sf::Event::Closed>()){ _window.close(); }
    }
}
