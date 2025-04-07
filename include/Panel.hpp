#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Component.hpp"
#include "ResourceManager.hpp"
#include "GameCore.hpp"
#include "Counter.hpp"
#include "StopWatch.hpp"
#include "Clickable.hpp"

class Panel : public Component, public Clickable
{
public:
    Panel(const sf::Vector2f size,
          const ResourceManager& resourceManager,
          GameCore& gameCore,
          const sf::Vector2f startPosition);

    void init();
    void update();

    virtual void onLeftClick(const sf::Vector2i mousePosition) override;

private:
    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;

    const ResourceManager& _resourceManager;
    GameCore& _gameCore;
    Button _restart;
    Counter _flags;
    StopWatch _stopWatch;
};