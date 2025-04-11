#include "GameCore.hpp"

GameCore::GameCore(const GameData& gameData,
                   const ResourceManager& resourceManager)
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _board(_gameData),
    _gameStatus(PlayState::RUN)
{
    setSize(sf::Vector2f(_gameData.rows * _gameData.cellSize, _gameData.columns * _gameData.cellSize));

    _textureBatches["hiddenCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    _textureBatches["mineCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    _textureBatches["flagCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    for(int i = 0; i < _gameData.cellNumberTexture.size(); i++)
    {
        _textureBatches[_gameData.cellNumberTexture[i]] = sf::VertexArray(sf::PrimitiveType::Triangles);
    }
}

void GameCore::init()
{
    _board.reset();
    _gameStatus = PlayState::RUN;
    _flags = 0;
    _firstMove = false;
}

void GameCore::toggleFlag(const sf::Vector2i& position)
{
    const Cell& cell = _board.getCell(position);
    if(cell.getState() == CellState::FLAG && _flags > 0)
    { 
        _board.unsetFlag(position); 
        _flags--;
    }
    else if(cell.getState() == CellState::HIDE && _flags < _gameData.mines)
    { 
        _board.setFlag(position); 
        _flags++;
    }   
}

bool GameCore::checkExplosion(const sf::Vector2i& position)
{
    const Cell& cell = _board.getCell(position);
    if(cell.isBomb() && cell.getState() != CellState::FLAG)
    {
        setGameLost();
        return true;
    }
    return false;
}

void GameCore::onRightClick(const sf::Vector2i& mousePosition)
{
    if(_gameStatus != PlayState::RUN || !isClicked(mousePosition)){ return; }
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition - sf::Vector2i(getPosition()));
    toggleFlag(cellPosition);    
    if(!_board.isAnyHiddenCell()){ setGameWin(); }
}

void GameCore::onLeftClick(const sf::Vector2i& mousePosition)
{
    if(_gameStatus != PlayState::RUN || !isClicked(mousePosition)){ return; }
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition - sf::Vector2i(getPosition()));
    if(!_firstMove)
    {
        _board.initializeMines(cellPosition);
        _firstMove = true;
    }
    if(checkExplosion(cellPosition)){ return; }
    searchNearbyMines(cellPosition);
    if(!_board.isAnyHiddenCell()){ setGameWin(); }
}

void GameCore::searchNearbyMines(const sf::Vector2i& position)
{
    std::stack<sf::Vector2i> st;
    st.push(position);
    while(!st.empty())
    {
        auto currentPosiotion = st.top();
        st.pop();
        const Cell& cell = _board.getCell(currentPosiotion);
        if(cell.getState() != CellState::HIDE || cell.isBomb()){ continue; }
        _board.showCell(currentPosiotion);
        if(cell.getNumber() > 0){ continue; }
        for(const auto& direction : gridUtils::directions)
        {
            sf::Vector2i newPosition = currentPosiotion + direction;
            if(_board.isCellInGrid(newPosition)){ st.push(newPosition); }
        }
    }
}

void GameCore::setGameLost(){ _gameStatus = PlayState::LOST; }

void GameCore::setGameWin(){ _gameStatus = PlayState::WIN; }

bool GameCore::isGameLost() const{ return _gameStatus == PlayState::LOST; }

bool GameCore::isGameWin() const { return _gameStatus == PlayState::WIN; }

bool GameCore::isGameRunning() const { return _gameStatus == PlayState::RUN; }

size_t GameCore::countFlags() const { return _gameData.mines - _flags; }

sf::Vector2f GameCore::getRealPosition(const sf::Vector2i& position) const
{
    return { (static_cast<float>(position.x) * _gameData.cellSize),
              (static_cast<float>(position.y) * _gameData.cellSize) };
}

void GameCore::addCell(const sf::Vector2i& position) const
{
    std::string texturePath = "hiddenCell.png";
    const Cell& cell = _board.getCell(position);
    if(cell.isBomb() && isGameLost()){ texturePath = "mineCell.png"; }
    else if(cell.getState() == CellState::UNHIDE){ texturePath = _gameData.cellNumberTexture[cell.getNumber()]; }
    else if(cell.getState() == CellState::FLAG){ texturePath = "flagCell.png"; }
            
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
            
    auto& batch = _textureBatches[texturePath];
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
    for(auto& pair : _textureBatches){ pair.second.clear(); }
    for(int i = 0; i < _gameData.rows; i++)
    {
        for(int j = 0; j < _gameData.columns; j++)
        {
            addCell({i, j});
        }
    }
    for(const auto& pair : _textureBatches) 
    {
        const std::string& texturePath = pair.first;
        const sf::VertexArray& batch = pair.second;
        
        if(batch.getVertexCount() <= 0){ continue; }
        sf::RenderStates batchStates = states;
        batchStates.texture = &_resourceManager.getTexture(texturePath);
        target.draw(batch, batchStates);
    }
}