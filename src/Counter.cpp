#include "Counter.hpp"

namespace gui
{
Counter::Counter(const sf::Vector2f& size, 
                 const sf::Vector2f& startPosition,
                 const ResourceManager& resourceManager,
                 const std::string& fontName)
    : _resourceManager(resourceManager),
    _value(0),
    _text(_resourceManager.getFont(fontName))
{
    setPosition(startPosition);
    setSize(size);
}

void Counter::setValue(size_t newValue){ _value = newValue; }

void Counter::incrementValue(){ _value++; }

void Counter::decrementValue(){ _value--; }

void Counter::draw(sf::RenderTarget& target, 
                   sf::RenderStates states) const
{
    states.transform *= getTransform();
    std::string str = std::to_string(_value);
    _text.setString(str);
    target.draw(_text, states);
}
}