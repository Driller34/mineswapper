#include "Button.hpp"
#include <iostream>

Button::Button(const sf::Vector2f size, 
               const ResourceManager& resourceManager,
               const std::string text,
               std::function<void()> onClick)
    : _shape(size),
      _resourceManager(resourceManager),
      _text(_resourceManager.getFont("digital-7.ttf"), text, 24),
      _onClick(std::move(onClick))
{
    setSize(size);
    _shape.setFillColor(sf::Color::Red);
}

void Button::onClick()
{
    if(_onClick){ _onClick(); }
}

void Button::draw(sf::RenderTarget& target, 
                  sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_shape, states);
    target.draw(_text, states);
}