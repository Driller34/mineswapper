#include "Board.hpp"

Board::Board(const GameData& gameData)
     : _gameData(gameData),
     _grid(_gameData.rows, _gameData.columns)
{
    reset();
}

void Board::reset()
{
    for(auto& cell : _grid){ cell.reset(); }
}

bool Board::isCellInGrid(const sf::Vector2i& position) const 
{
    return _grid.inBounds(position);
}

void Board::setFlag(const sf::Vector2i& position)
{
    _grid[position].setState(CellState::FLAG);
}

void Board::unsetFlag(const sf::Vector2i& position)
{
    _grid[position].setState(CellState::HIDE);
}

const Cell& Board::getCell(const sf::Vector2i& position) const
{
    return _grid[position];
}

void Board::initializeMines(const sf::Vector2i& banedPosition)
{
    const size_t index = _grid.index(banedPosition);
    setMines(index);
    mixMines(index);
    setNumbers();
}

void Board::setMines(const size_t bannedIndex)
{
    int index = 0;
    int mines = _gameData.mines;
    const int n = _grid.size();
    while(index < n && mines > 0)
    {
        if(index != bannedIndex)
        {
            _grid[index].setMine();
            mines--;
        }
        index++;
    }
}

void Board::mixMines(const size_t bannedIndex)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _grid.size() - 1);
    for(int i = 0; i < _gameData.mines; i++)
    {
        int random_number = dis(gen);
        if(random_number == bannedIndex){ continue; }
        std::swap(_grid[i], _grid[random_number]);
    }
}

void Board::setNumbers()
{
    for(int i = 0; i < _gameData.rows; i++)
    {
        for(int j = 0; j < _gameData.columns; j++)
        {
            if(_grid[{i, j}].isMine()){ addMines({i, j}); }
        }
    }
}

void Board::addMines(const sf::Vector2i& position)
{
    for(const auto& direction : gridUtils::directions)
    {
        sf::Vector2i newPosition = position + direction;
        if(isCellInGrid(newPosition)){ _grid[newPosition].addMine(); }
    }
}

void Board::showCell(const sf::Vector2i& position)
{
    _grid[position].setState(CellState::UNHIDE);
}

sf::Vector2i Board::getGridCoordsFromPosition(const sf::Vector2i& pixelPosition) const
{
    const int column = pixelPosition.x / _gameData.cellSize;
    const int row = pixelPosition.y / _gameData.cellSize;

    return { column, row };
}

bool Board::isAnyHiddenCell() const
{
    for(const auto& cell : _grid)
    {
        if(cell.getState() == CellState::HIDE){ return true; }
    }
    return false;
}
