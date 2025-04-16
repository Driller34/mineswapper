#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include <memory>
#include "GameState.hpp"

class GameStateManager
{
public:
    GameStateManager();

    void update();
    void render(sf::RenderWindow& window);
    void inputHandler(const sf::Event& event, 
                      sf::RenderWindow& window);

    void push(std::unique_ptr<GameState> state);
    void pop();
    void change(std::unique_ptr<GameState> state);
    GameState* top() const;
    bool empty() const;

private:
    std::stack<std::unique_ptr<GameState>> states;
};