#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <utility>
#include <unordered_map>
#include "Cell.hpp"
#include "GameData.hpp"
#include "ResourceManager.hpp"
#include "Component.hpp"

class Board
{
public:
    Board(const GameData& gameData);

    void reset();
    void setFlag(const sf::Vector2i position);
    void unsetFlag(const sf::Vector2i position);

    void toggleFlag(const sf::Vector2i position);

    void showCell(const sf::Vector2i position);
    Cell getCell(const sf::Vector2i position) const;
    bool isCellInGrid(const sf::Vector2i position) const;
    sf::Vector2i getCellFormPosition(const sf::Vector2i position) const;

private:
    void setMines();
    void mixMines();
    void setNumbers();

    void addBombs(const sf::Vector2i position);

    const GameData& _gameData;
    std::vector<std::vector<Cell>> _grid;
};