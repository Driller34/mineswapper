#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "Board.hpp"
#include "Cell.hpp"
#include "GameState.hpp"
#include "ResourceManager.hpp"
#include "GameCore.hpp"
#include "Container.hpp"
#include "Button.hpp"
#include "StopWatch.hpp"
#include "FlagCounter.hpp"
#include "GameSettings.hpp"
#include "utils.hpp"
#include "GameStateManager.hpp"
#include "WindowService.hpp"

class MainState : public GameState
{
public:
    MainState(GameStateManager& gameStateManager,
              const GameSettings& gameSettings,
              const ResourceManager& resourceManager,
              WindowService& windowService);

    virtual void init() override;
    virtual void update() override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void activateState() override;
    virtual void inputHandler(const sf::Event& event, 
                              sf::RenderWindow& window) override;
private:
    void onRightClick(const sf::Vector2f& cursorPosition);
    void onLeftClick(const sf::Vector2f& cursorPosition);

    GameStateManager& _gameStateManager;
    const GameSettings _gameSettings;
    const ResourceManager& _resourceManager;
    WindowService& _windowService;

    mineswapper::GameCore _gameCore;
    gui::Container _panel;
    gui::StopWatch* _stopWatch;
};