#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include "state/MainState.hpp"
#include "state/MenuState.hpp"
#include "engine/ResourceManager.hpp"
#include "state/GameStateManager.hpp"
#include "engine/utils.hpp"
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
