#pragma once
#include <SFML/Graphics.hpp>

class WindowService 
{
public:
    WindowService(sf::RenderWindow& window);

    void setResolution(const sf::Vector2u& size);
    const sf::RenderWindow& getWindow() const;
    sf::RenderWindow& accessWindow();

private:
    sf::RenderWindow& _window;
};
    