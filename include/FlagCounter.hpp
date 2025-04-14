#pragma once
#include <SFML/Graphics.hpp>
#include "Counter.hpp"
#include "Updatable.hpp"
#include "GameCore.hpp"

namespace gui
{
class FlagCounter : public Counter, public Updatable
{
public:
    FlagCounter(const sf::Vector2f& size,
                const sf::Vector2f& startPosition,
                const ResourceManager& resourceManager,
                GameCore& gameCore);

    virtual void update() override;

private:

    GameCore& _gameCore;
};
}