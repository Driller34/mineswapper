#include "MenuState.hpp"

MenuState::MenuState(GameStateManager& gameStateManager,
                     const ResourceManager& resourceManager,
                     WindowService& windowService) 
    : _gameStateManager(gameStateManager),
    _resourceManager(resourceManager),
    _windowService(windowService)
{
    init();
}

void MenuState::init()
{
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "Easy", sf::Vector2f(90.0f, 70.0f), [this](){ startGame(GameLevel::EASY); });
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "Medium", sf::Vector2f(90.0f, 140.0f), [this](){ startGame(GameLevel::MEDIUM); });
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "Hard", sf::Vector2f(90.0f, 210.0f), [this](){ startGame(GameLevel::HARD); });
    options.emplace_back(sf::Vector2f(100.0f, 60.0f), _resourceManager, "Exit",  sf::Vector2f(90.0f, 280.0f), [this](){ exitGame(); });
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

void MenuState::startGame(GameLevel level)
{
    GameSettings gameSettings{10, 10, 10};
    if(level == GameLevel::MEDIUM){ gameSettings = {20, 20, 20}; }
    else if(level == GameLevel::HARD){ gameSettings = {20, 30, 40}; }
    _windowService.setResolution({gameSettings.width(), gameSettings.height()});
    _gameStateManager.push(std::make_unique<MainState>(_gameStateManager, gameSettings, _resourceManager));    
}

void MenuState::exitGame()
{
    _gameStateManager.pop();
}