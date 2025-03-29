#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.hpp"
#include "GameData.hpp"
#include <random>

class Board : public sf::Drawable
{
public:
    Board(const GameData& gameData,
          const sf::Vector2f startPosition);

    void setFlag(const sf::Vector2i position);
    void unsetFlag(const sf::Vector2i position);
    void showCell(const sf::Vector2i position);
    Cell getCell(const sf::Vector2i position) const;
    sf::Vector2i getCellFormPosition(const sf::Vector2i position) const;
    bool isCellInGrid(const sf::Vector2i position) const;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
    
    void addCell(const sf::Vector2i position) const;
    void setMines();
    void mixMines();
    void setNumbers();

    void addBombs(const sf::Vector2i position);

    sf::Vector2f getPostion(const sf::Vector2i position) const;

    const GameData& _gameData;
    const sf::Vector2f _startPosition;
    mutable sf::VertexArray _cells;
    std::vector<std::vector<Cell>> _grid;
};