#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include "MainState.hpp"
#include "ResourceManager.hpp"

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
    ResourceManager _resourceManager;
    GameData _gameData;
    MainState _mainState;
};
