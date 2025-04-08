#include "GameCore.hpp"
#include <iostream>

GameCore::GameCore(const GameData& gameData,
                   const ResourceManager& resourceManager)
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _board(_gameData)
{
    setSize(sf::Vector2f(_gameData.rows * _gameData.cellSize, _gameData.columns * _gameData.cellSize));
}

void GameCore::init()
{
    hideMines();
    _board.reset();
    _gameLost = false;
    _gameWin = false;
    _flags = 0;
}

void GameCore::setGameLost()
{
    showMines();
    _gameLost = true;
}

void GameCore::setGameWin()
{
    _gameWin = true;
}

void GameCore::onRightClick(const sf::Vector2i mousePosition)
{
    if(_gameLost || _gameWin || !isClicked(mousePosition)){ return; }
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition - sf::Vector2i(getPosition()));
    const Cell& cell = _board.getCell(cellPosition);
    if(!_board.isAnyHiddenCell()){ setGameWin(); }

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
    if(_gameLost || _gameWin || !isClicked(mousePosition)){ return; }
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition - sf::Vector2i(getPosition()));
    const Cell& cell = _board.getCell(cellPosition);

    if(cell.isBomb() && cell.getState() != State::FLAG)
    {
        setGameLost();
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
        const Cell& cell = _board.getCell(pos);
        if(cell.getState() != State::HIDE || cell.isBomb()){ continue; }
        _board.showCell(pos);
        if(cell.getNumber() > 0){ continue; }
        for(const auto& dir : directions)
        {
            sf::Vector2i newPos = pos + dir;
            if(_board.isCellInGrid(newPos)){ st.push(newPos); }
        }
    }
}

bool GameCore::isGameLost() const
{
    return _gameLost;
}

bool GameCore::isGameWin() const
{
    return _gameWin;
}

void GameCore::showMines(){ _showMines = true; }

void GameCore::hideMines(){ _showMines = false; }

size_t GameCore::countFlags() const { return _gameData.mines - _flags; }

sf::Vector2f GameCore::getRealPosition(const sf::Vector2i position) const
{
    return { (static_cast<float>(position.x) * _gameData.cellSize),
              (static_cast<float>(position.y) * _gameData.cellSize) };
}

void GameCore::addCell(const sf::Vector2i position,
                       std::unordered_map<std::string, sf::VertexArray>& textureBatches) const
{
    std::string texturePath = "hiddenCell.png";
    const Cell& cell = _board.getCell(position);
    if(cell.isBomb() && _showMines){ texturePath = "mineCell.png"; }
    else if(cell.getState() == State::UNHIDE){ texturePath = _gameData.cellNumberTexture[cell.getNumber()]; }
    else if(cell.getState() == State::FLAG){ texturePath = "flagCell.png"; }
            
    sf::Vector2f size = { static_cast<float>(_gameData.cellSize - 2), static_cast<float>(_gameData.cellSize - 2) };
    sf::Vector2f realPosition = getRealPosition(position);

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

void GameCore::draw(sf::RenderTarget& target, 
                    sf::RenderStates states) const
{
    states.transform *= getTransform();
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