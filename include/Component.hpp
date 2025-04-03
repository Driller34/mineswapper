#pragma once
#include <SFML/Graphics.hpp>

class Component : public sf::Drawable, public sf::Transformable
{
public:
    virtual ~Component() = default;
    virtual sf::FloatRect getLocalBounds() const
    {
        return sf::FloatRect(getPosition(), getSize());
    }
    sf::FloatRect getGlobalBounds() const
    {
        return getTransform().transformRect(getLocalBounds());
    }

    virtual void setSize(const sf::Vector2f& size){ _size = size; }
    virtual sf::Vector2f getSize() const { return _size; }

private:
    sf::Vector2f _size = {0.0f, 0.0f};
};