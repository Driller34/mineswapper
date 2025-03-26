#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include "Board.hpp"

class Game
{
public:
    Game();

    void run();
    void update();
    void render();
    void processEvent();

private:
    sf::RenderWindow _window;
    GameData _gameData;
    Board _board;
};
