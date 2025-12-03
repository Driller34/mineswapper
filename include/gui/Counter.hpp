#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Component.hpp"
#include "engine/ResourceManager.hpp"

namespace gui
{
class Counter : public Component
{
public:
    Counter(const sf::Vector2f& size, 
            const sf::Vector2f& startPosition,
            const ResourceManager& resourceManager,
            const std::string& fontName = "digital-7.ttf");

    void setValue(size_t newValue);
    void incrementValue();
    void decrementValue();

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
                      
    const ResourceManager& _resourceManager;
    size_t _value;
    mutable sf::Text _text;
};
}