#include "Button.hpp"

Button::Button(const sf::Vector2f size, 
               const std::string text)
    : _shape(size)
{
    _shape.setFillColor(sf::Color::Red);

}

void Button::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_shape);
}