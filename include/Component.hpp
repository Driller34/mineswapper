#pragma once
#include <SFML/Graphics.hpp>

namespace GUI
{

class Component
{
public:
    ~Component() = default;

    virtual void isActive() const;
    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event& event) = 0;
private:
    bool _isActivate{false};

};

}