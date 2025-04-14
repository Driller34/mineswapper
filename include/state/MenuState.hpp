#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <string.h>
#include "GameState.hpp"
#include "MainState.hpp"
#include "GameStateManager.hpp"
#include "ResourceManager.hpp"
#include "Button.hpp"
#include "GameData.hpp"

class MenuState : public GameState
{
public:
    MenuState(GameStateManager& gameStateManager,
              const ResourceManager& resourceManager,
            GameData& gameData);

    virtual void init() override;
    virtual void update() override;
    virtual void draw(sf::RenderWindow& window) override;
    virtual void inputHandler(const sf::Event& event, 
                              sf::RenderWindow& window) override;

private:
    GameStateManager& _gameStateManager;
    const ResourceManager& _resourceManager;

    GameData& _gameData;

    std::vector<gui::Button> options;

    void startGame1();
    void startGame2();
    void startGame3();

    void onLeftClick(const sf::Vector2i& mousePosition);
    void onRightClick(const sf::Vector2i& mousePosition);

    void exitGame();
};