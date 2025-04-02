#pragma once
#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "ResourceManager.hpp"

class Button : public Component
{
public:
    Button(const sf::Vector2f size, 
           const ResourceManager& resourceManager,
           const std::string text,
           std::function<void()> onClick);

    void onClick();

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
    
    sf::RectangleShape _shape;
    const ResourceManager& _resourceManager;
    std::function<void()> _onClick;
};
