#include "GameLogic.hpp"

namespace mineswapper
{
GameLogic::GameLogic(const GameSettings& gameSettings,
                     Board& board)
    : _gameSettings(gameSettings),
    _board(board),
    _flags(0),
    _firstMove(false),
    _playState(PlayState::RUN){}

void GameLogic::reset()
{
    _flags = 0;
    _firstMove = false;
    _playState = PlayState::RUN;
}

PlayState GameLogic::getPlayState() const 
{ 
    return _playState; 
}

void GameLogic::toggleFlag(const sf::Vector2i& position)
{
    const Cell& cell = _board.getCell(position);
    if(cell.getState() == CellState::FLAG && _flags > 0)
    { 
        _board.unsetFlag(position); 
        _flags--;
    }
    else if(cell.getState() == CellState::HIDE && _flags < _gameSettings.mines)
    { 
        _board.setFlag(position); 
        _flags++;
    }   
    if(!_board.isAnyHiddenCell()){ setGameWin(); }
}

void GameLogic::dig(const sf::Vector2i& position)
{
    if(!_firstMove)
    {
        _board.initializeMines(position);
        _firstMove = true;
    }
    if(checkExplosion(position)){ return; }
    searchNearbyMines(position);
    if(!_board.isAnyHiddenCell()){ setGameWin(); }
}

void GameLogic::searchNearbyMines(const sf::Vector2i& position)
{
    std::stack<sf::Vector2i> st;
    st.push(position);
    while(!st.empty())
    {
        auto currentPosiotion = st.top();
        st.pop();
        const Cell& cell = _board.getCell(currentPosiotion);
        if(cell.getState() != CellState::HIDE || cell.isMine()){ continue; }
        _board.showCell(currentPosiotion);
        if(cell.getNumber() > 0){ continue; }
        for(const auto& direction : gridUtils::directions)
        {
            sf::Vector2i newPosition = currentPosiotion + direction;
            if(_board.isCellInGrid(newPosition)){ st.push(newPosition); }
        }
    }
}

bool GameLogic::checkExplosion(const sf::Vector2i& position)
{
    const Cell& cell = _board.getCell(position);
    if(cell.isMine() && cell.getState() != CellState::FLAG)
    {
        setGameLost();
        return true;
    }
    return false;
}

void GameLogic::setGameLost()
{ 
    _playState = PlayState::LOST;
}

void GameLogic::setGameWin()
{ 
    _playState = PlayState::WIN; 
}

size_t GameLogic::countFlags() const 
{ 
    return _gameSettings.mines - _flags; 
}
}