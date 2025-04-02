#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "Component.hpp"
#include "ResourceManager.hpp"
#include "Cell.hpp"
#include "GameData.hpp"
#include "Board.hpp"

class GameCore : public Component
{
public:
    GameCore(const GameData& gameData,
             const ResourceManager& resourceManager);

    void init();

    void onRightClick(const sf::Vector2i mousePosition);
    void onLeftClick(const sf::Vector2i mousePosition);

    void searchNearbyMines(const sf::Vector2i position);
    bool isGameOver() const;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    void setMines();
    void mixMines();
    void setNumbers();
    void setGameOver();

    const ResourceManager& _resourceManager;
    Board _board;
    const GameData& _gameData;
    bool _gameOver{false};
    int _flags{0};
};