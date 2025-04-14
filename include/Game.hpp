#pragma once
#include <SFML/Graphics.hpp>
#include "MainState.hpp"
#include "MenuState.hpp"
#include "ResourceManager.hpp"
#include "GameStateManager.hpp"
#include "utils.hpp"
#include "WindowService.hpp"

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
    GameStateManager _gameStateManager;
    WindowService _windowService;
};
