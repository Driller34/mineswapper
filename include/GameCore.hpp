#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "Component.hpp"
#include "ResourceManager.hpp"
#include "Cell.hpp"
#include "GameData.hpp"
#include "Board.hpp"
#include "Clickable.hpp"

class GameCore : public Component, public Clickable
{
    enum class Status {RUN, LOST, WIN};
public:
    GameCore(const GameData& gameData,
             const ResourceManager& resourceManager);

    void init();

    virtual void onRightClick(const sf::Vector2i mousePosition) override;
    virtual void onLeftClick(const sf::Vector2i mousePosition) override;

    void searchNearbyMines(const sf::Vector2i position);
    bool isGameLost() const;
    bool isGameWin() const;

    size_t countFlags() const;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    void addCell(const sf::Vector2i position,
                 std::unordered_map<std::string, sf::VertexArray>& textureBatches) const;

    void setGameLost();
    void setGameWin();

    void toggleFlag(const sf::Vector2i& position);
    bool checkExplosion(const sf::Vector2i& position);
    sf::Vector2f getRealPosition(const sf::Vector2i position) const;

    const ResourceManager& _resourceManager;
    Board _board;
    const GameData& _gameData;
    mutable sf::VertexArray _cells;
    Status _gameStatus;
    
    size_t _flags{0};

    static constexpr std::array<sf::Vector2i, 8> directions = {
        sf::Vector2i(1, 0), sf::Vector2i(-1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, -1), 
        sf::Vector2i(1, 1), sf::Vector2i(-1, -1), sf::Vector2i(-1, 1), sf::Vector2i(1, -1)
    };
};