#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Component.hpp"
#include "ResourceManager.hpp"

class Counter : public Component
{
public:
    Counter(const sf::Vector2f size, 
            const ResourceManager& resourceManager);

    void setValue(size_t newValue);
    void incrementValue();
    void decrementValue();

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
                      
    const ResourceManager& _resourceManager;
    size_t _value{0};
    mutable sf::Text _text;
    sf::Font _font;
};