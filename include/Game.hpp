#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include "MainState.hpp"

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
    MainState _mainState;
};
