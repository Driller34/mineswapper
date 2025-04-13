#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include "MainState.hpp"
#include "ResourceManager.hpp"
#include "GameStateManager.hpp"

class Game
{
public:
    Game();
    void run();
private:
    void update();
    void render();
    void processEvent();

    sf::RenderWindow _window;
    ResourceManager _resourceManager;
    GameData _gameData;
    GameStateManager _gameStateManager;
};
