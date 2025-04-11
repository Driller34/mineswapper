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
    enum class PlayState {RUN, LOST, WIN};
public:
    GameCore(const GameData& gameData,
             const ResourceManager& resourceManager);

    void reset();

    virtual void onRightClick(const sf::Vector2i& mousePosition) override;
    virtual void onLeftClick(const sf::Vector2i& mousePosition) override;

    void searchNearbyMines(const sf::Vector2i& position);
    bool isGameLost() const;
    bool isGameWin() const;
    bool isGameRunning() const;
    size_t countFlags() const;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    void addCell(const sf::Vector2i& position) const;

    void setGameLost();
    void setGameWin();

    void toggleFlag(const sf::Vector2i& position);
    bool checkExplosion(const sf::Vector2i& position);

    sf::Vector2f getRealPosition(const sf::Vector2i& position) const;

    const ResourceManager& _resourceManager;
    Board _board;
    PlayState _gameStatus;
    const GameData& _gameData;
    mutable sf::VertexArray _cells;
    mutable std::unordered_map<std::string, sf::VertexArray> _textureBatches;
    
    size_t _flags{0};

    bool _firstMove{false};
};