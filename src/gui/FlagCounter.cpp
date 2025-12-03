#include "gui/FlagCounter.hpp"

namespace gui
{
FlagCounter::FlagCounter(const sf::Vector2f& size,
                         const sf::Vector2f& startPosition,
                         const ResourceManager& resourceManager,
                         mineswapper::GameCore& gameCore,
                         const std::string& fontName)
    : Counter(size, startPosition, resourceManager, fontName),
    _gameCore(gameCore)
{

}

void FlagCounter::update()
{
    setValue(_gameCore.countFlags());
}
}