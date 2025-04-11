#pragma once
#include <SFML/Graphics.hpp>

namespace gridUtils
{
    constexpr std::array<sf::Vector2i, 8> directions = {
        sf::Vector2i(1, 0), sf::Vector2i(-1, 0), sf::Vector2i(0, 1), sf::Vector2i(0, -1), 
        sf::Vector2i(1, 1), sf::Vector2i(-1, -1), sf::Vector2i(-1, 1), sf::Vector2i(1, -1)
    };
}