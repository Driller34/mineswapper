#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"

class Panel : public sf::Drawable
{
public:
    Panel(const sf::Vector2f size,
          const sf::Vector2f startPosition);

    void init();
    void update();

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    sf::Vector2f _size;
    sf::Vector2f _startPosition;

    Button _restart;
    //Counter _mines;
    //Counter _time;
};