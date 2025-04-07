#include "StopWatch.hpp"

StopWatch::StopWatch(const sf::Vector2f& size,
                     const ResourceManager& resourceManager,
                     float delaySeconds)
    : Counter(size, resourceManager),
    _delaySeconds(delaySeconds),
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
    if(_clock.getElapsedTime().asSeconds() >= _delaySeconds)
    {
        incrementValue();
        _clock.restart();
    }
}

void StopWatch::stop(){ _stop = true; }

void StopWatch::start(){ _stop = false; }