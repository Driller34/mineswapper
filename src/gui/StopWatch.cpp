#include "gui/StopWatch.hpp"

namespace gui
{
StopWatch::StopWatch(const sf::Vector2f& size,
                     const sf::Vector2f& startPosition,
                     const ResourceManager& resourceManager,
                     sf::Time delay,
                     const std::string& fontName)
    : Counter(size, startPosition, resourceManager, fontName),
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
}