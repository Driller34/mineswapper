#pragma once
#include <SFML/Graphics.hpp>

class Panel : public sf::Drawable
{
public:
    Panel();

    void init();
    void update();

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    Button _restart;
    Counter _mines;
    Counter _time;
};