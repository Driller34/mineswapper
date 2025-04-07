#include "StopWatch.hpp"

StopWatch::StopWatch(const sf::Vector2f& size,
                     const ResourceManager& resourceManager,
                     sf::Time delay)
    : Counter(size, resourceManager),
    _delay(delay),
    _clock()
{
}


void StopWatch::restart()
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