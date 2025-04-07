#pragma once
#include <SFML/Graphics.hpp>
#include "Counter.hpp"

class StopWatch : public Counter
{
public:
    StopWatch(const sf::Vector2f& size,
              const ResourceManager& resourceManager,
              sf::Time delay = sf::seconds(1.0f));


    void update();
    void restart();
    void stop();
    void start();

private:
    sf::Time _delay;
    bool _stop{false};
    sf::Clock _clock;
};