#pragma once
#include <SFML/Graphics.hpp>
#include "GameData.hpp"
#include "Board.hpp"
#include "GameState.hpp"

class MainState : public GameState
{
public:
    MainState(const GameData& gameData);

    virtual void init() override;
    virtual void update() override;
    virtual void draw(sf::RenderWindow& window) override;

    void onRightClick(const sf::Vector2i mousePosition);
    void onLeftClick(const sf::Vector2i mousePosition);

private:

    void setFlag(const sf::Vector2i position);
    void searchNearbyMines(const sf::Vector2i position);
    bool isGameOver() const;

    Board _board;
    const GameData& _gameData;
    bool gameOver{false};
};