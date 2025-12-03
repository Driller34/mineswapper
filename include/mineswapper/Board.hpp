#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <utility>
#include <unordered_map>
#include "mineswapper/Cell.hpp"
#include "engine/utils.hpp"
#include "mineswapper/Grid.hpp"
#include "mineswapper/GameSettings.hpp"

namespace mineswapper
{
class Board
{
public:
    Board(const GameSettings& gameSettings);

    void reset();
    void setFlag(const sf::Vector2i& position);
    void unsetFlag(const sf::Vector2i& position);

    void showCell(const sf::Vector2i& position);
    const Cell& getCell(const sf::Vector2i& position) const;
    bool isCellInGrid(const sf::Vector2i& position) const;

    void initializeMines(const sf::Vector2i& banedPosition);

    bool isAnyHiddenCell() const;
private:
    void setMines(const size_t bannedIndex);
    void mixMines(const size_t bannedIndex);
    void setNumbers();

    void addMines(const sf::Vector2i& position);

    const GameSettings& _gameSettings;
    Grid<Cell> _grid;
};
}