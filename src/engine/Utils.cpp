#include "engine/utils.hpp"

namespace windowUtils
{
    sf::Vector2f getWorldMousePosition(const sf::RenderWindow& window)
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        const sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
    
        return worldPosition;
    }
}