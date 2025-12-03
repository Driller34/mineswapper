#include "gui/Container.hpp"

namespace gui
{
Container::Container(const sf::Vector2f& size)
{
    setSize(size);
}

void Container::push(std::unique_ptr<Component> component)
{
    if(auto* updatable = dynamic_cast<Updatable*>(component.get()))
    {
        _updatables.push_back(updatable);
    }
    if(auto* clickable = dynamic_cast<Clickable*>(component.get()))
    {
        _clickables.push_back(clickable);
    }
    _components.push_back(std::move(component));
}

void Container::update()
{
    for(auto& component : _updatables)
    {
        component->update();
    }
}

void Container::onLeftClick(const sf::Vector2f& cursorPosition)
{
    for(auto& component : _clickables)
    {
        component->onLeftClick(cursorPosition);
    }
}

void Container::onRightClick(const sf::Vector2f& cursorPosition)
{
    for(auto& component : _clickables)
    {
        component->onLeftClick(cursorPosition);
    }
}

void Container::draw(sf::RenderTarget& target, 
                     sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (const auto& component : _components)
    {
        target.draw(*component, states);
    }
}
}