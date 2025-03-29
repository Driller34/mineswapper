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
    else if(cell.getState() == State::HIDE){ _board.setFlag(cellPosition); }   
}

void MainState::onLeftClick(const sf::Vector2i mousePosition)
{
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition);
    Cell cell = _board.getCell(cellPosition);
    if(cell.getState() == State::HIDE)
    { 
        searchNearbyMines(cellPosition);
    }
}

void MainState::searchNearbyMines(const sf::Vector2i position)
{
    std::stack<sf::Vector2i> st;
    st.push(position);
    while(!st.empty())
    {
        auto pos = st.top();
        st.pop();
        auto cell = _board.getCell(pos);
        if(cell.getState() != State::HIDE || cell.isBomb()){ continue; }
        _board.showCell(pos);
        if(cell.getNumber() > 0){ continue; }
        std::array<sf::Vector2i, 8> directions = {
            sf::Vector2i(1, 0), sf::Vector2i(-1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, -1), 
            sf::Vector2i(1, 1), sf::Vector2i(-1, -1), sf::Vector2i(-1, 1), sf::Vector2i(1, -1)
        };
        for(const auto& dir : directions)
        {
            sf::Vector2i newPos = pos + dir;
            if(_board.isCellInGrid(newPos)){ st.push(newPos); }
        }
    }
}
