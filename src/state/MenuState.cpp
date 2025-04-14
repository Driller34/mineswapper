#include "MenuState.hpp"

MenuState::MenuState(GameStateManager& gameStateManager,
                     const ResourceManager& resourceManager,
                     GameData& gameData) 
    : _gameStateManager(gameStateManager),
    _resourceManager(resourceManager),
    _gameData(gameData)
{
    init();
}

void MenuState::init()
{
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "10x10", sf::Vector2f(110.0f, 70.0f), [this](){ startGame1(); });
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "20x20", sf::Vector2f(110.0f, 140.0f), [this](){ startGame2(); });
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "40x40", sf::Vector2f(110.0f, 210.0f), [this](){ startGame3(); });
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "Exit",  sf::Vector2f(110.0f, 280.0f), [this](){ exitGame(); });
}


void MenuState::update(){}

void MenuState::draw(sf::RenderWindow& window)
{
    for(int i = 0; i < options.size(); i++)
    {
        window.draw(options[i]);
    }
}

void MenuState::inputHandler(const sf::Event& event, 
                             sf::RenderWindow& window)
{
    if(const auto* mouseEvent = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if(mouseEvent->button == sf::Mouse::Button::Right)
        {
            onRightClick(sf::Mouse::getPosition(window));
        }
        if(mouseEvent->button == sf::Mouse::Button::Left)
        {
            onLeftClick(sf::Mouse::getPosition(window));
        }
    }
}

void MenuState::onLeftClick(const sf::Vector2i& mousePosition)
{
    for(auto& option : options)
    {
        option.onLeftClick(mousePosition);
    }
}

void MenuState::onRightClick(const sf::Vector2i& mousePosition)
{
    for(auto& option : options)
    {
        option.onRightClick(mousePosition);
    }
}

void MenuState::startGame1()
{
    _gameData.setData(10, 10, 10);
    _gameStateManager.push(std::make_unique<MainState>(_gameData, _resourceManager));    
}

void MenuState::startGame2()
{
    _gameData.setData(20, 20, 20);
    _gameStateManager.push(std::make_unique<MainState>(_gameData, _resourceManager));      
}

void MenuState::startGame3()
{
    _gameData.setData(40, 40, 40);
    _gameStateManager.push(std::make_unique<MainState>(_gameData, _resourceManager));       
}


void MenuState::exitGame()
{
    _gameStateManager.pop();
}