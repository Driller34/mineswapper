#include "MainState.hpp"
#include <iostream>

MainState::MainState(const GameData& gameData,
                     ResourceManager& resourceManager) 
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _board(_gameData, _resourceManager, {0.0f, 0.0f})
{

}

void MainState::init()
{

}

void MainState::update()
{
    if(_gameOver)
    {
        std::cout<<"gameOver\n";
    }
}

void MainState::draw(sf::RenderWindow& window)
{
    window.draw(_board);
}

void MainState::onRightClick(const sf::Vector2i mousePosition)
{
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition);
    Cell cell = _board.getCell(cellPosition);
    if(cell.getState() == State::FLAG && _flags > 0)
    { 
        _board.unsetFlag(cellPosition); 
        _flags--;
    }
    else if(cell.getState() == State::HIDE && _flags < _gameData.mines)
    { 
        _board.setFlag(cellPosition); 
        _flags++;
    }   
}

void MainState::onLeftClick(const sf::Vector2i mousePosition)
{
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition);
    Cell cell = _board.getCell(cellPosition);
    if(cell.isBomb())
    {
        _gameOver = true;
        return;
    }
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
