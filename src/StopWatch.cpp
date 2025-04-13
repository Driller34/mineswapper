#include "StopWatch.hpp"

StopWatch::StopWatch(const sf::Vector2f& size,
                     const ResourceManager& resourceManager,
                     sf::Time delay)
    : Counter(size, resourceManager),
    _stop(false),
    _delay(delay),
    _clock()
{
}


void StopWatch::reset()
{
    setValue(0);
}

void StopWatch::update()
{
    if(_stop){ return; }
    if(_clock.getElapsedTime() >= _delay)
    {
        incrementValue();
        _clock.restart();
    }
}

void StopWatch::stop(){ _stop = true; }

void StopWatch::start(){ _stop = false; }