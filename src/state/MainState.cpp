#include "MainState.hpp"


MainState::MainState(const GameSettings& gameSettings,
                     const ResourceManager& resourceManager) 
    : _gameSettings(gameSettings),
    _resourceManager(resourceManager),
    _gameCore(_gameSettings, _resourceManager),
    _panel(sf::Vector2f(_gameSettings.width(), conf::panelHeight()))
    
{
    _gameCore.setPosition(conf::startPosition());
    _panel.setPosition(conf::panelPosition());
    auto stopWatch = std::make_unique<gui::StopWatch>(
        sf::Vector2f(180.0f, 100.0f),
        conf::stopWatchPosition(), 
        _resourceManager
    );

    _stopWatch = stopWatch.get(); 
    _panel.push(std::move(stopWatch));   

    _panel.push(std::make_unique<gui::Button>(
        sf::Vector2f(100.0f, 60.0f),
        _resourceManager,
        "Restart",
        conf::resetPosition(),
        [&]() { _gameCore.reset(); _stopWatch->reset(); }
    ));

    _panel.push(std::make_unique<gui::FlagCounter>(
        sf::Vector2f(180.0f, 100.0f),
        conf::flagCounterPosition(),
        _resourceManager,
        _gameCore
    ));
}

void MainState::init()
{
    
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
            onRightClick(sf::Mouse::getPosition(window));
        }
        if(mouseEvent->button == sf::Mouse::Button::Left)
        {
            onLeftClick(sf::Mouse::getPosition(window));
        }
    }
}

void MainState::onRightClick(const sf::Vector2i& mousePosition)
{
    _gameCore.onRightClick(mousePosition); 
}

void MainState::onLeftClick(const sf::Vector2i& mousePosition)
{
    _gameCore.onLeftClick(mousePosition);
    _panel.onLeftClick(mousePosition);
}