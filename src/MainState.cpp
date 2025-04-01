#include "MainState.hpp"
#include <iostream>

MainState::MainState(const GameData& gameData,
                     ResourceManager& resourceManager) 
    : _gameData(gameData),
    _resourceManager(resourceManager),
    _board(_gameData, _resourceManager),
    _panel(sf::Vector2f(_gameData.PanelWidth, _gameData.PanelHeight), {0.0f, 0.0f})
{
    _board.setPosition(_gameData.startPosition);
}

void MainState::init()
{

}

void MainState::update()
{
    if(_gameOver)
    {
        _board.showMines();
    }
}

void MainState::draw(sf::RenderWindow& window)
{
    window.draw(_panel);
    window.draw(_board);
}

void MainState::onRightClick(const sf::Vector2i mousePosition)
{
   if(_board.getLocalBounds().contains(sf::Vector2f(mousePosition))){ boardRightClick(mousePosition); }
   if(_panel.getLocalBounds().contains(sf::Vector2f(mousePosition)))
   {
        std::cout<<"click\n";
        _panel.onRightClick(mousePosition);
   }
}

void MainState::onLeftClick(const sf::Vector2i mousePosition)
{
    if(_board.getLocalBounds().contains(sf::Vector2f(mousePosition))){ boardLeftClick(mousePosition); }
}

void MainState::boardRightClick(const sf::Vector2i mousePosition)
{
    if(_gameOver){ return; }
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

void MainState::boardLeftClick(const sf::Vector2i mousePosition)
{
    if(_gameOver){ return; }
    const sf::Vector2i cellPosition = _board.getCellFormPosition(mousePosition);
    Cell cell = _board.getCell(cellPosition);
    if(cell.isBomb() && cell.getState() != State::FLAG)
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
