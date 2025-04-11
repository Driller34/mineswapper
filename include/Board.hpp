#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <utility>
#include <unordered_map>
#include "Cell.hpp"
#include "GameData.hpp"
#include "Component.hpp"
#include "utils.hpp"

class Board
{
public:
    Board(const GameData& gameData);

    void reset();
    void setFlag(const sf::Vector2i& position);
    void unsetFlag(const sf::Vector2i& position);

    void showCell(const sf::Vector2i& position);
    const Cell& getCell(const sf::Vector2i& position) const;
    bool isCellInGrid(const sf::Vector2i& position) const;
    sf::Vector2i getGridCoordsFromPosition(const sf::Vector2i& pixelPosition) const;

    void initializeMines(const sf::Vector2i& banedPosition);

    bool isAnyHiddenCell() const;
private:
    void setMines(const size_t bannedIndex);
    void mixMines(const size_t bannedIndex);
    void setNumbers();

    void addMines(const sf::Vector2i& position);

    size_t getIndex(const sf::Vector2i& position) const;

    const GameData& _gameData;
    std::vector<Cell> _grid;
};