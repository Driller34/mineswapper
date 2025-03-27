#include "MainState.hpp"
#include <iostream>

MainState::MainState(const GameData& gameData) 
    : _gameData(gameData),
    _board(_gameData, {0.0f, 0.0f})
{

}

void MainState::init()
{

}

void MainState::update()
{

}

void MainState::draw(sf::RenderWindow& window)
{
    window.draw(_board);
}

void MainState::onRightClick(const sf::Vector2i mousePosition)
{
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition);
    Cell cell = _board.getCell(cellPosition);
    if(cell.getState() == State::FLAG){ _board.unsetFlag(cellPosition); }
    else{ _board.setFlag(cellPosition); }   
}

void MainState::onLeftClick(const sf::Vector2i mousePosition)
{
}