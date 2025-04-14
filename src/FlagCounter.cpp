#include "FlagCounter.hpp"

namespace gui
{
FlagCounter::FlagCounter(const sf::Vector2f& size,
                         const sf::Vector2f& startPosition,
                         const ResourceManager& resourceManager,
                         GameCore& gameCore)
    : Counter(size, startPosition, resourceManager),
    _gameCore(gameCore)
{

}

void FlagCounter::update()
{
    setValue(_gameCore.countFlags());
}
}