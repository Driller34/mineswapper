#include "Board.hpp"
#include <iostream>

Board::Board(const GameData& gameData,
             const ResourceManager& resourceManager)
     : _gameData(gameData),
     _resourceManager(resourceManager),
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

void Board::showMines()
{
    _showMines = true;
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
    const sf::Vector2f startPosition = getPosition();
    const sf::Vector2i relativePosition = position - sf::Vector2i(startPosition.x, startPosition.y);
    
    const int column = relativePosition.x / _gameData.cellSize;
    const int row = relativePosition.y / _gameData.cellSize;

    return { column, row };
}

sf::Vector2f Board::getPostion(const sf::Vector2i position) const
{
    const sf::Vector2f startPosition = getPosition();
    return { startPosition.x + (position.x * _gameData.cellSize),
             startPosition.y+ (position.y * _gameData.cellSize) };
} 

void Board::addCell(const sf::Vector2i position,
                    std::unordered_map<std::string, sf::VertexArray>& textureBatches) const
{
    std::string texturePath = "hiddenCell.png";
    auto cell = _grid[position.x][position.y];
    if(cell.isBomb() && _showMines){ texturePath = "mineCell.png"; }
    else if(cell.getState() == State::UNHIDE){ texturePath = _gameData.cellNumberTexture[cell.getNumber()]; }
    else if(cell.getState() == State::FLAG){ texturePath = "flagCell.png"; }
            
    sf::Vector2f size = { static_cast<float>(_gameData.cellSize - 2), static_cast<float>(_gameData.cellSize - 2) };
    sf::Vector2f realPosition = getPostion(position);

    sf::Vector2f topLeft = realPosition;
    sf::Vector2f topRight = sf::Vector2f(realPosition.x + size.x, realPosition.y);
    sf::Vector2f bottomLeft = sf::Vector2f(realPosition.x, realPosition.y + size.y);
    sf::Vector2f bottomRight = sf::Vector2f(realPosition.x + size.x, realPosition.y + size.y);
            
    sf::Texture& texture = _resourceManager.getTexture(texturePath);
    sf::Vector2f texSize = sf::Vector2f(texture.getSize());
    sf::Vector2f texTopLeft = sf::Vector2f(0.f, 0.f);
    sf::Vector2f texTopRight = sf::Vector2f(texSize.x, 0.f);
    sf::Vector2f texBottomLeft = sf::Vector2f(0.f, texSize.y);
    sf::Vector2f texBottomRight = sf::Vector2f(texSize.x, texSize.y);
            
    auto& batch = textureBatches[texturePath];
    batch.append(sf::Vertex(topLeft, sf::Color::White, texTopLeft));
    batch.append(sf::Vertex(bottomLeft, sf::Color::White, texBottomLeft));
    batch.append(sf::Vertex(bottomRight, sf::Color::White, texBottomRight));

    batch.append(sf::Vertex(topLeft, sf::Color::White, texTopLeft));
    batch.append(sf::Vertex(bottomRight, sf::Color::White, texBottomRight));
    batch.append(sf::Vertex(topRight, sf::Color::White, texTopRight));
}

void Board::draw(sf::RenderTarget& target, 
                 sf::RenderStates states) const
{
    _cells.clear();
    std::unordered_map<std::string, sf::VertexArray> textureBatches;
    textureBatches["hiddenCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    textureBatches["mineCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    textureBatches["flagCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    for(int i = 0; i < _gameData.cellNumberTexture.size(); i++)
    {
        textureBatches[_gameData.cellNumberTexture[i]] = sf::VertexArray(sf::PrimitiveType::Triangles);
    }
    for(int i = 0; i < _gameData.rows; i++)
    {
        for(int j = 0; j < _gameData.columns; j++)
        {
            addCell({i, j}, textureBatches);
        }
    }
    for(const auto& pair : textureBatches) 
    {
        const std::string& texturePath = pair.first;
        const sf::VertexArray& batch = pair.second;
        
        if(batch.getVertexCount() <= 0){ continue; }
        sf::RenderStates batchStates = states;
        batchStates.texture = &_resourceManager.getTexture(texturePath);
        target.draw(batch, batchStates);
    }
}