#pragma once
#include <SFML/Graphics.hpp>

struct GameData
{
    unsigned int cellSize = 30;
    unsigned int rows = 10;
    unsigned int columns = 10;
    unsigned int mines = 10;

    size_t counterFontSize = 24;

    std::array<std::string, 9> cellNumberTexture = {
        "emptyCell.png", "1.png", "2.png", "3.png", "4.png",
        "5.png", "6.png", "7.png", "8.png"
    };

    unsigned int panelWidth() const { return cellSize * columns; }
    unsigned int panelHeight() const { return cellSize * 4; }
    unsigned int width() const { return cellSize * columns; }
    unsigned int height() const { return (cellSize * rows) + panelHeight(); }

    sf::Vector2f panelPosition = {0.0f, 0.0f};

    sf::Vector2f startPosition() const { return {0.0f, static_cast<float>(panelHeight())}; }
    sf::Vector2f flagCounterPosition() const { return {10.0f, panelHeight() / 2.0f - 20.0f}; }
    sf::Vector2f resetPosition() const { return {panelWidth() / 2.0f - 50.0f, panelHeight() / 2.0f - 20.0f}; }
    sf::Vector2f stopWatchPosition() const { return {panelWidth() - 50.0f, panelHeight() / 2.0f - 20.0f}; }
};
