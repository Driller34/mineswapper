#pragma once
#include <SFML/Graphics.hpp>
#include "Counter.hpp"
#include "Updatable.hpp"

class StopWatch : public Counter, public Updatable
{
public:
    StopWatch(const sf::Vector2f& size,
              const ResourceManager& resourceManager,
              const sf::Vector2f& startPosition,
              sf::Time delay = sf::seconds(1.0f));

    virtual void update() override;
    void reset();
    void stop();
    void start();

private:
    sf::Time _delay;
    bool _stop;
    sf::Clock _clock;
};