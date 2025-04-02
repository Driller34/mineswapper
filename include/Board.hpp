#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <utility>
#include <unordered_map>
#include "Cell.hpp"
#include "GameData.hpp"
#include "ResourceManager.hpp"
#include "Component.hpp"

//mines is logic
class Board : public sf::Drawable
{
public:
    Board(const GameData& gameData,
          const ResourceManager& resourceManager);

    void reset();
    void setFlag(const sf::Vector2i position);
    void unsetFlag(const sf::Vector2i position);
    void showCell(const sf::Vector2i position);
    void showMines();
    void hideMines();
    Cell getCell(const sf::Vector2i position) const;
    sf::Vector2i getCellFormPosition(const sf::Vector2i position) const;
    bool isCellInGrid(const sf::Vector2i position) const;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
    
    void addCell(const sf::Vector2i position,
                 std::unordered_map<std::string, sf::VertexArray>& textureBatches) const;
    void setMines();
    void mixMines();
    void setNumbers();

    void addBombs(const sf::Vector2i position);

    sf::Vector2f getRealPosition(const sf::Vector2i position) const;

    const ResourceManager& _resourceManager;
    const GameData& _gameData;
    mutable sf::VertexArray _cells;
    std::vector<std::vector<Cell>> _grid;
    
    bool _showMines{false};
};