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
                mineswapper::GameCore& gameCore,
                const std::string& fontName = "digital-7.ttf");

    virtual void update() override;

private:

    mineswapper::GameCore& _gameCore;
};
}