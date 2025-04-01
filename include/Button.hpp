#pragma once
#include <SFML/Graphics.hpp>

class Button : public sf::Drawable, public sf::Transformable
{
public:
    Button(const sf::Vector2f size, 
           const std::string text);

    void onClick();

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
    
    sf::RectangleShape _shape;
    //sf::Text _text;
    bool _isHovered{false};
    bool _isPressed{false};
};