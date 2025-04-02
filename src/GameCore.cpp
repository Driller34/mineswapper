#include "GameCore.hpp"
#include <iostream>

GameCore::GameCore(const GameData& gameData,
                   const ResourceManager& resourceManager)
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _board(_gameData, _resourceManager)
{
    setSize(sf::Vector2f(_gameData.rows * _gameData.cellSize, _gameData.columns * _gameData.cellSize));
    //_board.setPosition(getPosition());
}

void GameCore::init()
{

}

void GameCore::onRightClick(const sf::Vector2i mousePosition)
{
    if(_gameOver){ return; }
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition - sf::Vector2i(getPosition()));
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

void GameCore::onLeftClick(const sf::Vector2i mousePosition)
{
    if(_gameOver){ return; }
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition - sf::Vector2i(getPosition()));
    Cell cell = _board.getCell(cellPosition);
    if(cell.isBomb() && cell.getState() != State::FLAG)
    {
        _board.showMines();
        _gameOver = true;
        return;
    }
    if(cell.getState() == State::HIDE){ searchNearbyMines(cellPosition); }
}

void GameCore::searchNearbyMines(const sf::Vector2i position)
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

bool GameCore::isGameOver() const
{
    return _gameOver;
}

void GameCore::setMines()
{

}
void GameCore::mixMines()
{

}
void GameCore::setNumbers()
{

}

void GameCore::draw(sf::RenderTarget& target, 
                    sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_board, states);
}