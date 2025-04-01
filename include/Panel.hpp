#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Component.hpp"

class Panel : public Component
{
public:
    Panel(const sf::Vector2f size,
          const sf::Vector2f startPosition);

    void init();
    void update();

    void onRightClick(const sf::Vector2i mousePosition);
    void onLeftClick(const sf::Vector2i mousePosition);

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    Button _restart;
    //Counter _mines;
    //Counter _time;
};