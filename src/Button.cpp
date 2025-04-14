#include "Button.hpp"

namespace gui
{
Button::Button(const sf::Vector2f& size, 
               const ResourceManager& resourceManager,
               const std::string& text,
               const sf::Vector2f& startPosition,
               std::function<void()> onClick,
               const std::string& fontName,
               const size_t fontSize,
               const sf::Color color)
    : _shape(size),
      _resourceManager(resourceManager),
      _text(_resourceManager.getFont(fontName), text, fontSize),
      _onClick(std::move(onClick))
{
    setSize(size);
    setPosition(startPosition);
    _shape.setFillColor(sf::Color::Red);
}

void Button::onLeftClick(const sf::Vector2i& mousePosition)
{
    if(!isClicked(mousePosition)){ return; }
    if(_onClick){ _onClick(); }
}

void Button::draw(sf::RenderTarget& target, 
                  sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(_shape, states);
    target.draw(_text, states);
}
}