#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "GameData.hpp"
#include "Board.hpp"
#include "Cell.hpp"
#include "GameState.hpp"
#include "ResourceManager.hpp"
#include "Panel.hpp"

class MainState : public GameState
{
public:
    MainState(const GameData& gameData,
              ResourceManager& resourceManager);

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

    ResourceManager& _resourceManager;
    Board _board;
    Panel _panel;
    const GameData& _gameData;
    bool _gameOver{false};
    int _flags{0};
};