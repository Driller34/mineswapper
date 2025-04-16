#include "GameStateManager.hpp"

GameStateManager::GameStateManager(){}

void GameStateManager::push(std::unique_ptr<GameState> state)
{
    states.push(std::move(state));
    states.top()->activateState();
}

void GameStateManager::pop()
{
    if(!states.empty()){ states.pop(); }
    if(!states.empty()){ states.top()->activateState(); }
}

void GameStateManager::change(std::unique_ptr<GameState> state)
{
    while(!states.empty())
    {
        states.pop();
    }
    states.push(std::move(state));
    states.top()->activateState();
}

bool GameStateManager::empty() const
{
    return states.empty();
}

GameState* GameStateManager::top() const
{
    return states.empty() ? nullptr : states.top().get();
}

void GameStateManager::update()
{
    if(states.empty()){ return; }
    states.top()->update();
}

void GameStateManager::render(sf::RenderWindow& window)
{
    if(states.empty()){ return; }
    states.top()->draw(window);
}

void GameStateManager::inputHandler(const sf::Event& event, sf::RenderWindow& window)
{
    if(states.empty()){ return; }
    states.top()->inputHandler(event, window);
}