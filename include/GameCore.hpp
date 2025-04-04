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
    bool isGameWin() const;

    int getHiddenMines() const;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    void addCell(const sf::Vector2i position,
                 std::unordered_map<std::string, sf::VertexArray>& textureBatches) const;

    void setGameOver();

    void showMines();
    void hideMines();
    sf::Vector2f getRealPosition(const sf::Vector2i position) const;

    const ResourceManager& _resourceManager;
    Board _board;
    const GameData& _gameData;
    mutable sf::VertexArray _cells;
    bool _gameOver{false};
    int _flags{0};
    bool _showMines{false};

    static constexpr std::array<sf::Vector2i, 8> directions = {
        sf::Vector2i(1, 0), sf::Vector2i(-1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, -1), 
        sf::Vector2i(1, 1), sf::Vector2i(-1, -1), sf::Vector2i(-1, 1), sf::Vector2i(1, -1)
    };
};