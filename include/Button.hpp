#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable
{
public:
    Button();

private:
    virtual void draw(sf::RenderTarget& target, 
                      f::RenderStates states) const override;
    
    sf::Vector2f _startPosition;
    sf::Vector2f _size;
};