#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <string.h>
#include "state/GameState.hpp"
#include "state/MainState.hpp"
#include "state/GameStateManager.hpp"
#include "engine/ResourceManager.hpp"
#include "gui/Button.hpp"
#include "mineswapper/GameSettings.hpp"
#include "WindowService.hpp"

class MenuState : public GameState
{
    enum class GameLevel{EASY, MEDIUM, HARD};
public:
    MenuState(GameStateManager& gameStateManager,
              const ResourceManager& resourceManager,
              WindowService& windowService);

    virtual void init() override;
    virtual void update() override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void activateState() override;
    virtual void inputHandler(const sf::Event& event, 
                              sf::RenderWindow& window) override;

private:
    void startGame(GameLevel level);

    void onLeftClick(const sf::Vector2f& cursorPosition);
    void onRightClick(const sf::Vector2f& cursorPosition);

    void exitGame();

    GameStateManager& _gameStateManager;
    const ResourceManager& _resourceManager;
    WindowService& _windowService;

    std::vector<gui::Button> options;
};