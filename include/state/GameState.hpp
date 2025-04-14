#pragma once
#include <SFML/Graphics.hpp>
#include "Updatable.hpp"

class GameState : public Updatable
{
public:
    virtual ~GameState() = default;
    virtual void init() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void inputHandler(const sf::Event& event, 
                              sf::RenderWindow& window) = 0;
};