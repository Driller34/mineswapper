#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "GameData.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "GameState.hpp"
#include "ResourceManager.hpp"
#include "Panel.hpp"
#include "GameCore.hpp"

class MainState : public GameState
{
public:
    MainState(const GameData& gameData,
              const ResourceManager& resourceManager);

    virtual void init() override;
    virtual void update() override;
    virtual void draw(sf::RenderWindow& window) override;

    void onRightClick(const sf::Vector2i mousePosition);
    void onLeftClick(const sf::Vector2i mousePosition);
private:

    void setFlag(const sf::Vector2i position);
    void searchNearbyMines(const sf::Vector2i position);
    bool isGameOver() const;

    void boardRightClick(const sf::Vector2i mousePosition);
    void boardLeftClick(const sf::Vector2i mousePosition);

    const ResourceManager& _resourceManager;
    const GameData& _gameData;
    Panel _panel;

    GameCore _gameCore;
};