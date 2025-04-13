#pragma once
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Component.hpp"
#include "ResourceManager.hpp"
#include "GameCore.hpp"
#include "Counter.hpp"
#include "StopWatch.hpp"
#include "Clickable.hpp"

class Container : public Component, public Clickable
{
public:
    Container(const sf::Vector2f& size)

    void push(std::unique_ptr<Component> component);
    void update();
    void draw();

private:

    std::vector<std::unique_ptr<Component>> _components;
};