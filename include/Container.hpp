#pragma once
#include <SFML/Graphics.hpp>
#include "Component.hpp"
#include "Clickable.hpp"
#include "Updatable.hpp"

class Container : public Component, public Clickable, public Updatable
{
public:
    Container(const sf::Vector2f& size);

    void push(std::unique_ptr<Component> component);
    virtual void update() override;

    virtual void onLeftClick(const sf::Vector2i& mousePosition) override;

    virtual void draw(sf::RenderTarget& target, 
                      sf::RenderStates states) const override;
private:

    std::vector<std::unique_ptr<Component>> _components;
    std::vector<Clickable*> _clickables;
    std::vector<Updatable*> _updatables;
};