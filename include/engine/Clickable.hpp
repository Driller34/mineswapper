#pragma once
#include <SFML/Graphics.hpp>

class Clickable
{
public:
    virtual ~Clickable() = default;
    
    virtual void onRightClick(const sf::Vector2f& cursorPosition){};
    virtual void onLeftClick(const sf::Vector2f& coursorPosition){};
};