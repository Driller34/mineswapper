#pragma once
#include <SFML/Graphics.hpp>

namespace gridUtils
{
    constexpr std::array<sf::Vector2i, 8> directions = {
        sf::Vector2i(1, 0), sf::Vector2i(-1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, -1), 
        sf::Vector2i(1, 1), sf::Vector2i(-1, -1), sf::Vector2i(-1, 1), sf::Vector2i(1, -1)
    };
}

namespace conf
{
    constexpr unsigned int width{300};
    constexpr unsigned int height{400};

    constexpr size_t cellSize{30};
    constexpr size_t counterFontSize{24};

    constexpr unsigned int FRAMERATELIMIT = 60;

    constexpr std::array<std::string, 9> cellNumberTexture = {
        "emptyCell.png", "1.png", "2.png", "3.png", "4.png",
        "5.png", "6.png", "7.png", "8.png"
    };

    inline size_t panelHeight() { return cellSize * 4; }
    inline size_t panelWidth(size_t columns) { return columns * cellSize; }

    inline sf::Vector2f panelPosition()
    {
        return {0.0f, 0.0f};
    }

    inline sf::Vector2f flagCounterPosition(size_t windowWidth = width)
    {
        return {10.0f, static_cast<float>(panelHeight()) / 2.0f - 20.0f}; 
    }

    inline sf::Vector2f resetPosition(size_t windowWidth = width)
    {
        return {static_cast<float>(windowWidth) / 2.0f, static_cast<float>(panelHeight()) / 2.0f - 20.0f};
    }

    inline sf::Vector2f escapePosition(size_t windowWidth = width)
    {
        return {static_cast<float>(windowWidth) / 2.0f - 60.0f, static_cast<float>(panelHeight()) / 2.0f - 20.0f};
    }

    inline sf::Vector2f startPosition()
    {
        return {0.0f, static_cast<float>(panelHeight())};
    }

    inline sf::Vector2f stopWatchPosition(size_t columns = 10)
    {
        return {
            static_cast<float>(panelWidth(columns)) - 50.0f,
            static_cast<float>(panelHeight()) / 2.0f - 20.0f
        };
    }
}