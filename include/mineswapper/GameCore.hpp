#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "Component.hpp"
#include "ResourceManager.hpp"
#include "Cell.hpp"
#include "Board.hpp"
#include "Clickable.hpp"
#include "GameLogic.hpp"
#include "GameSettings.hpp"
#include "utils.hpp"

namespace mineswapper
{
class GameCore : public Component, public Clickable
{
public:
    GameCore(const GameSettings& gameSettings,
             const ResourceManager& resourceManager);

    void reset();

    virtual void onRightClick(const sf::Vector2f& cursorPosition) override;
    virtual void onLeftClick(const sf::Vector2f& cursorPosition) override;

    bool isGameLost() const;
    bool isGameWin() const;
    bool isGameRunning() const;
    size_t countFlags() const;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    void addCell(const sf::Vector2i& position) const;

    sf::Vector2f getRealPosition(const sf::Vector2i& position) const;
    sf::Vector2i getGridCoordsFromPosition(const sf::Vector2f& cursorPosition) const;

    const ResourceManager& _resourceManager;
    const GameSettings& _gameSettings;
    Board _board;
    GameLogic _gameLogic;
    mutable sf::VertexArray _cells;
    mutable std::unordered_map<std::string, sf::VertexArray> _textureBatches;
};
}