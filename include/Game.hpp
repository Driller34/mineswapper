#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include "MainState.hpp"
#include "MenuState.hpp"
#include "ResourceManager.hpp"
#include "GameStateManager.hpp"
#include "utils.hpp"

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
