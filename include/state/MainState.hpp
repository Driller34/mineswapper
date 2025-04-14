#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "GameData.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "GameState.hpp"
#include "ResourceManager.hpp"
#include "GameCore.hpp"
#include "Container.hpp"
#include "Button.hpp"
#include "StopWatch.hpp"
#include "FlagCounter.hpp"

class MainState : public GameState
{
public:
    MainState(const GameData& gameData,
              const ResourceManager& resourceManager);

    virtual void init() override;
    virtual void update() override;
    virtual void draw(sf::RenderWindow& window) override;

    virtual void inputHandler(const sf::Event& event, 
                              sf::RenderWindow& window) override;
private:
    void onRightClick(const sf::Vector2i& mousePosition);
    void onLeftClick(const sf::Vector2i& mousePosition);

    const ResourceManager& _resourceManager;
    const GameData& _gameData;
    GameCore _gameCore;
    gui::Container _panel;
    gui::StopWatch* _stopWatch;
};