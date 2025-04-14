#include "GameCore.hpp"

GameCore::GameCore(const GameSettings& gameSettings,
                   const ResourceManager& resourceManager)
    : _gameSettings(gameSettings),
    _resourceManager(resourceManager),
    _board(_gameSettings),
    _gameLogic(_gameSettings, _board)
{
    setSize(sf::Vector2f(_gameSettings.rows * conf::cellSize, _gameSettings.columns * conf::cellSize));

    _textureBatches["hiddenCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    _textureBatches["mineCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    _textureBatches["flagCell.png"] = sf::VertexArray(sf::PrimitiveType::Triangles);
    for(int i = 0; i < conf::cellNumberTexture.size(); i++)
    {
        _textureBatches[conf::cellNumberTexture[i]] = sf::VertexArray(sf::PrimitiveType::Triangles);
    }
}

void GameCore::reset()
{
    _board.reset();
    _gameLogic.reset();
}

void GameCore::onRightClick(const sf::Vector2i& mousePosition)
{
    if(!isGameRunning() || !isClicked(mousePosition)){ return; }
    const sf::Vector2i cellPosition = _board.getGridCoordsFromPosition(mousePosition - sf::Vector2i(getPosition()));
    _gameLogic.toggleFlag(cellPosition);
}

void GameCore::onLeftClick(const sf::Vector2i& mousePosition)
{
    if(!isGameRunning() || !isClicked(mousePosition)){ return; }
    const sf::Vector2i cellPosition = _board.getGridCoordsFromPosition(mousePosition - sf::Vector2i(getPosition()));
    _gameLogic.dig(cellPosition);
}

bool GameCore::isGameLost() const
{ 
    return _gameLogic.getPlayState() == PlayState::LOST; 
}

bool GameCore::isGameWin() const 
{ 
    return _gameLogic.getPlayState() == PlayState::WIN; 
}

bool GameCore::isGameRunning() const 
{ 
    return _gameLogic.getPlayState() == PlayState::RUN; 
}

size_t GameCore::countFlags() const 
{ 
    return _gameLogic.countFlags(); 
}

sf::Vector2f GameCore::getRealPosition(const sf::Vector2i& position) const
{
    return { (static_cast<float>(position.x) * conf::cellSize),
              (static_cast<float>(position.y) * conf::cellSize) };
}

void GameCore::addCell(const sf::Vector2i& position) const
{
    std::string texturePath = "hiddenCell.png";
    const Cell& cell = _board.getCell(position);
    if(cell.isMine() && isGameLost()){ texturePath = "mineCell.png"; }
    else if(cell.getState() == CellState::UNHIDE){ texturePath = conf::cellNumberTexture[cell.getNumber()]; }
    else if(cell.getState() == CellState::FLAG){ texturePath = "flagCell.png"; }
            
    sf::Vector2f size = { static_cast<float>(conf::cellSize - 2), static_cast<float>(conf::cellSize - 2) };
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
    for(int i = 0; i < _gameSettings.rows; i++)
    {
        for(int j = 0; j < _gameSettings.columns; j++)
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