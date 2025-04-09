#include "Board.hpp"
#include <iostream>

Board::Board(const GameData& gameData)
     : _gameData(gameData),
     _grid(_gameData.rows * _gameData.columns)
{
    reset();
}

void Board::reset()
{
    for(auto& cell : _grid){ cell.reset(); }
    setMines();
    mixMines();
    setNumbers();
}

bool Board::isCellInGrid(const sf::Vector2i position) const 
{
    return position.x >= 0 && position.x < _gameData.rows && position.y >= 0 && position.y < _gameData.columns;
}

void Board::setFlag(const sf::Vector2i position)
{
    _grid[getIndex(position)].setState(State::FLAG);
}

void Board::unsetFlag(const sf::Vector2i position)
{
    _grid[getIndex(position)].setState(State::HIDE);
}

const Cell& Board::getCell(const sf::Vector2i position) const
{
    return _grid[getIndex(position)];
}

void Board::setMines()
{
    for(int i = 0; i < _gameData.mines; i++)
    {
        _grid[i].setBomb();
    }
}

void Board::mixMines()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _grid.size() - 1);

    for(int i = 0; i < _gameData.mines; i++)
    {
        int random_number = dis(gen);
        std::swap(_grid[i], _grid[random_number]);
    }
}

void Board::setNumbers()
{
    for(int i = 0; i < _gameData.rows; i++)
    {
        for(int j = 0; j < _gameData.columns; j++)
        {
            if(_grid[getIndex({i, j})].isBomb()){ addBombs({i, j}); }
        }
    }
}

void Board::addBombs(const sf::Vector2i position)
{
    if(isCellInGrid({position.x + 1, position.y})){ _grid[getIndex(position + sf::Vector2i(1, 0))].addBomb(); }
    if(isCellInGrid({position.x + 1, position.y + 1})){ _grid[getIndex(position + sf::Vector2i(1, 1))].addBomb(); }
    if(isCellInGrid({position.x - 1, position.y})){ _grid[getIndex(position + sf::Vector2i(-1, 0))].addBomb(); }
    if(isCellInGrid({position.x - 1, position.y - 1})){ _grid[getIndex(position + sf::Vector2i(-1, -1))].addBomb(); }
    if(isCellInGrid({position.x, position.y + 1})){ _grid[getIndex(position + sf::Vector2i(0, 1))].addBomb(); }
    if(isCellInGrid({position.x, position.y - 1})){ _grid[getIndex(position + sf::Vector2i(0, -1))].addBomb(); }
    if(isCellInGrid({position.x - 1, position.y + 1})){ _grid[getIndex(position + sf::Vector2i(-1, 1))].addBomb(); }
    if(isCellInGrid({position.x + 1, position.y - 1})){ _grid[getIndex(position + sf::Vector2i(1, -1))].addBomb(); }
}

void Board::showCell(const sf::Vector2i position)
{
    _grid[getIndex(position)].setState(State::UNHIDE);
}

sf::Vector2i Board::getCellFormPosition(const sf::Vector2i position) const
{
    const sf::Vector2i relativePosition = position;
    
    const int column = relativePosition.x / _gameData.cellSize;
    const int row = relativePosition.y / _gameData.cellSize;

    return { column, row };
}

bool Board::isAnyHiddenCell() const
{
    for(const auto& cell : _grid)
    {
        if(cell.getState() == State::HIDE){ return true; }
    }
    return false;
}

size_t Board::getIndex(const sf::Vector2i position) const
{
    return (position.x * _gameData.columns) + position.y;
}
