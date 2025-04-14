#pragma once
#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "ResourceManager.hpp"
#include "Clickable.hpp"

namespace gui
{
class Button : public Component, public Clickable
{
public:
    Button(const sf::Vector2f& size, 
           const ResourceManager& resourceManager,
           const std::string& text,
           const sf::Vector2f& startPosition,
           std::function<void()> onClick);

    virtual void onLeftClick(const sf::Vector2i& mousePosition) override;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
    
    const ResourceManager& _resourceManager;
    sf::Text _text;
    sf::RectangleShape _shape;
    std::function<void()> _onClick;
};
}