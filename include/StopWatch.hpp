#pragma once
#include <SFML/Graphics.hpp>
#include "Counter.hpp"
#include "Updatable.hpp"

namespace gui
{
class StopWatch : public Counter, public Updatable
{
public:
    StopWatch(const sf::Vector2f& size,
              const sf::Vector2f& startPosition,
              const ResourceManager& resourceManager,
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
}