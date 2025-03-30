#include "Board.hpp"
#include <iostream>

Board::Board(const GameData& gameData,
             const ResourceManager& resourceManager,
             const sf::Vector2f startPosition)
     : _gameData(gameData),
     _resourceManager(resourceManager),
     _startPosition(startPosition),
     _grid(_gameData.rows, std::vector<Cell>(_gameData.columns)),
     _cells(sf::PrimitiveType::Triangles)
{
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
    if(!isCellInGrid(position)){ return; }
    _grid[position.x][position.y].setState(State::FLAG);
}

void Board::unsetFlag(const sf::Vector2i position)
{
    _grid[position.x][position.y].setState(State::HIDE);
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
            if(_grid[i][j].isBomb()){ addBombs({i, j}); }
        }
    }
}

void Board::addBombs(const sf::Vector2i position)
{
    if(isCellInGrid({position.x + 1, position.y})){ _grid[position.x + 1][position.y].addBomb(); }
    if(isCellInGrid({position.x + 1, position.y + 1})){ _grid[position.x + 1][position.y + 1].addBomb(); }
    if(isCellInGrid({position.x - 1, position.y})){ _grid[position.x - 1][position.y].addBomb(); }
    if(isCellInGrid({position.x - 1, position.y - 1})){ _grid[position.x - 1][position.y - 1].addBomb(); }
    if(isCellInGrid({position.x, position.y + 1})){ _grid[position.x][position.y + 1].addBomb(); }
    if(isCellInGrid({position.x, position.y - 1})){ _grid[position.x][position.y - 1].addBomb(); }
    if(isCellInGrid({position.x - 1, position.y + 1})){ _grid[position.x - 1][position.y + 1].addBomb(); }
    if(isCellInGrid({position.x + 1, position.y - 1})){ _grid[position.x + 1][position.y - 1].addBomb(); }
}

void Board::showCell(const sf::Vector2i position)
{
    _grid[position.x][position.y].setState(State::UNHIDE);
}

sf::Vector2i Board::getCellFormPosition(const sf::Vector2i position) const
{
    sf::Vector2i relativePosition = position - sf::Vector2i(_startPosition.x, _startPosition.y);
    
    const int column = relativePosition.x / _gameData.cellSize;
    const int row = relativePosition.y / _gameData.cellSize;

    return { column, row };
}

sf::Vector2f Board::getPostion(const sf::Vector2i position) const
{
    return { _startPosition.x + (position.x * _gameData.cellSize),
             _startPosition.y+ (position.y * _gameData.cellSize) };
} 

sf::VertexArray Board::addCell(const sf::Vector2i position) const
{
    sf::Vector2f size = {static_cast<float>(_gameData.cellSize - 2), static_cast<float>(_gameData.cellSize - 2)};
    
    std::string texturePath = "hiddenCell.png";
    const auto& cell = _grid[position.x][position.y];
    if (cell.isBomb()) texturePath = "mineCell.png";
    else if (cell.getState() == State::UNHIDE) texturePath = _gameData.cellNumberTexture[cell.getNumber()];
    else if (cell.getState() == State::FLAG) texturePath = "flagCell.png";

    sf::Texture& texture = _resourceManager.getTexture(texturePath);
    sf::Vector2f realPosition = getPostion(position);

    // Wierzchołki prostokąta
    sf::VertexArray vertices(sf::Quads, 4);

    vertices[0].position = realPosition;
    vertices[1].position = {realPosition.x + size.x, realPosition.y};
    vertices[2].position = {realPosition.x, realPosition.y + size.y};
    vertices[3].position = {realPosition.x + size.x, realPosition.y + size.y};

    // Ustawienie tekstury
    for (int i = 0; i < 4; ++i)
    {
        vertices[i].texCoords = vertices[i].position; // Właściwe mapowanie tekstury na wierzchołki
    }

    // Ustawienie tekstury dla wierzchołków
    for (int i = 0; i < 4; ++i)
    {
        vertices[i].color = sf::Color::White;  // Ustawienie koloru wierzchołków na biały (tekstura je ożywi)
    }

    return vertices;
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::VertexArray vertexArray(sf::Quads);

    for (int i = 0; i < _gameData.rows; i++)
    {
        for (int j = 0; j < _gameData.columns; j++)
        {
            sf::VertexArray cellVertices = addCell({i, j});
            for (size_t k = 0; k < cellVertices.getVertexCount(); ++k)
            {
                vertexArray.append(cellVertices[k]);
            }
        }
    }

    target.draw(vertexArray, states);
}
