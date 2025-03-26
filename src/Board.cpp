#include "Board.hpp"

Board::Board(const GameData& gameData,
             const sf::Vector2f startPosition)
     : _gameData(gameData),
     _startPosition(startPosition),
     _grid(_gameData.rows, std::vector<Cell>(_gameData.columns)),
     _cells(sf::PrimitiveType::Triangles)
{
    setMines();
    mixMines();
}

bool Board::isCellInGrid(const sf::Vector2i position) const 
{
    return position.x >= 0 && position.x < _gameData.rows && position.y >= 0 && position.y < _gameData.columns;
}

void Board::setFlag(const sf::Vector2i position)
{
    if(!isCellInGrid(position)){ return; }
    _grid[position.x][position.y].setState(State::FLAG);
}

Cell Board::getCell(const sf::Vector2i position) const
{
    return _grid[position.x][position.y];
}

void Board::setMines()
{
    for(int i = 0; i < _gameData.mines; i++)
    {
        _grid[i % _gameData.rows][i / _gameData.rows].setBomb();
    }
}

void Board::mixMines()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _gameData.rows * _gameData.columns);

    for(int i = 0; i < _gameData.mines; i++)
    {
        int random_number = dis(gen);
        std::swap(_grid[i % _gameData.rows][i / _gameData.rows],
                  _grid[random_number % _gameData.rows][random_number / _gameData.rows]);
    }
}

void Board::setNumbers()
{
    for(int i = 0; i < _gameData.rows; i++)
    {
        for(int j = 0; j < _gameData.columns; j++)
        {
            
        }
    }
}

sf::Vector2f Board::getPostion(const sf::Vector2i position) const
{
    return { _startPosition.x + (position.x * _gameData.cellSize),
             _startPosition.y+ (position.y * _gameData.cellSize) };
} 

void Board::addCell(const sf::Vector2i position) const
{
    sf::Vector2f size = { static_cast<float>(_gameData.cellSize - 2), static_cast<float>(_gameData.cellSize - 2) };
    sf::Color color = sf::Color::Red;
    if(_grid[position.x][position.y].isBomb()){ color = sf::Color::Green; }
    sf::Vector2f realPosition = getPostion(position);

    _cells.append({realPosition, color});
    _cells.append({{realPosition.x + size.x, realPosition.y}, color});
    _cells.append({{realPosition.x + size.x, realPosition.y + size.y}, color});

    _cells.append({realPosition, color});
    _cells.append({{realPosition.x + size.x, realPosition.y + size.y}, color});
    _cells.append({{realPosition.x, realPosition.y + size.y}, color});
}


void Board::draw(sf::RenderTarget& target, 
                 sf::RenderStates states) const
{
    _cells.clear();
    for(int i = 0; i < _gameData.rows; i++)
    {
        for(int j = 0; j < _gameData.columns; j++)
        {
            addCell({i, j});
        }
    }
    target.draw(_cells);
}