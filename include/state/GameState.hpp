#pragma once
#include <SFML/Graphics.hpp>
#include "engine/Updatable.hpp"

class GameState : public Updatable
{
public:
    virtual ~GameState() = default;
    virtual void init() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void activateState() = 0;
    virtual void inputHandler(const sf::Event& event, 
                              sf::RenderWindow& window) = 0;
};