#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "mineswapper/Board.hpp"
#include "mineswapper/Cell.hpp"
#include "state/GameState.hpp"
#include "engine/ResourceManager.hpp"
#include "mineswapper/GameCore.hpp"
#include "gui/Container.hpp"
#include "gui/Button.hpp"
#include "gui/StopWatch.hpp"
#include "gui/FlagCounter.hpp"
#include "mineswapper/GameSettings.hpp"
#include "engine/utils.hpp"
#include "state/GameStateManager.hpp"
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