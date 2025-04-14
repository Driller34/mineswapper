#include "WindowService.hpp"

WindowService::WindowService(sf::RenderWindow& window)
    : _window(window)
{}

void WindowService::setResolution(const sf::Vector2u& size)
{
    _window.setSize(size);
    _window.setView(sf::View(sf::FloatRect(sf::Vector2f(0.f, 0.f), sf::Vector2f(size))));
}
    
const sf::RenderWindow& WindowService::getWindow() const
{
    return _window;
}
    
sf::RenderWindow& WindowService::accessWindow()
{
    return _window;
}