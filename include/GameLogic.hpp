#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "Cell.hpp"
#include "GameData.hpp"
#include "Board.hpp"
#include "GameSettings.hpp"

enum class PlayState {RUN, LOST, WIN};

class GameLogic
{
public:
    GameLogic(const GameSettings& gameSettings,
              Board& board);

    void searchNearbyMines(const sf::Vector2i& position);
    void reset();
    PlayState getPlayState() const;
    size_t countFlags() const;
    void toggleFlag(const sf::Vector2i& position);
    void dig(const sf::Vector2i& position);

private:
    void setGameLost();
    void setGameWin();

    bool checkExplosion(const sf::Vector2i& position);
    
    Board& _board;
    PlayState _playState;
    const GameSettings& _gameSettings;

    size_t _flags;
    bool _firstMove;
};