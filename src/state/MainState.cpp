#include "MainState.hpp"


MainState::MainState(GameStateManager& gameStateManager,
                     const GameSettings& gameSettings,
                     const ResourceManager& resourceManager,
                     WindowService& windowService) 
    : _gameStateManager(gameStateManager),
    _gameSettings(gameSettings),
    _resourceManager(resourceManager),
    _windowService(windowService),
    _gameCore(_gameSettings, _resourceManager),
    _panel(sf::Vector2f(_gameSettings.width(), conf::panelHeight()))
    
{
    init();
}

void MainState::init()
{
    _gameCore.setPosition(conf::startPosition());
    _panel.setPosition(conf::panelPosition());
    auto stopWatch = std::make_unique<gui::StopWatch>(
        sf::Vector2f(180.0f, 100.0f),
        conf::stopWatchPosition(_gameSettings.columns), 
        _resourceManager
    );

    _stopWatch = stopWatch.get(); 
    _panel.push(std::move(stopWatch));   

    _panel.push(std::make_unique<gui::Button>(
        sf::Vector2f(40.0f, 40.0f),
        _resourceManager,
        "RST",
        conf::resetPosition(_gameSettings.width()),
        [&]() { _gameCore.reset(); _stopWatch->reset(); }
    ));

    _panel.push(std::make_unique<gui::Button>(
        sf::Vector2f(40.0f, 40.0f),
        _resourceManager,
        "ESC",
        conf::escapePosition(_gameSettings.width()),
        [&]() { _gameStateManager.pop(); }
    ));

    _panel.push(std::make_unique<gui::FlagCounter>(
        sf::Vector2f(180.0f, 100.0f),
        conf::flagCounterPosition(_gameSettings.width()),
        _resourceManager,
        _gameCore
    ));
}

void MainState::activateState()
{
    _windowService.setResolution({_gameSettings.width(), _gameSettings.height()});
}

void MainState::update()
{
    _panel.update();
    if(!_gameCore.isGameRunning()){ _stopWatch->stop(); }
    else{ _stopWatch->start(); }
}

void MainState::draw(sf::RenderWindow& window)
{
    window.draw(_panel);
    window.draw(_gameCore);
}

void MainState::inputHandler(const sf::Event& event, 
                             sf::RenderWindow& window)
{
    if(const auto* mouseEvent = event.getIf<sf::Event::MouseButtonReleased>())
    {
        if(mouseEvent->button == sf::Mouse::Button::Right)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
            onRightClick(worldPosition);
        }
        if(mouseEvent->button == sf::Mouse::Button::Left)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
            onLeftClick(worldPosition);
        }
    }
}

void MainState::onRightClick(const sf::Vector2f& cursorPosition)
{
    _gameCore.onRightClick(cursorPosition); 
}

void MainState::onLeftClick(const sf::Vector2f& cursorPosition)
{
    _gameCore.onLeftClick(cursorPosition);
    _panel.onLeftClick(cursorPosition);
}