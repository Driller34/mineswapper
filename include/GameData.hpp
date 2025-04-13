#pragma once
#include <SFML/Graphics.hpp>

struct GameData
{
   static constexpr unsigned int cellSize{30};
   static constexpr unsigned int rows{20};
   static constexpr unsigned int columns{20}; 
   static constexpr unsigned int mines{20};

   static constexpr unsigned int PanelWidth{cellSize * columns};
   static constexpr unsigned int PanelHeight{cellSize * 4};

   static constexpr unsigned int width{cellSize * columns};
   static constexpr unsigned int height{(cellSize * rows) + PanelHeight};

   static constexpr sf::Vector2f panelPosition = {0.0f, 0.0f};

   static constexpr sf::Vector2f startPosition = {0.0f, static_cast<float>(PanelHeight)};

   static constexpr sf::Vector2f flagCounterPosition = {panelPosition.x + 10.0f, panelPosition.y + PanelHeight / 2 - 20.0f};

   static constexpr sf::Vector2f resetPosition = {panelPosition.x + PanelWidth / 2 - 50.0f, panelPosition.y + PanelHeight / 2 - 20.0f};

   static constexpr sf::Vector2f stopWatchPosition = {panelPosition.x + PanelWidth - 50.0f, panelPosition.y + PanelHeight / 2 - 20.0f};

   static constexpr size_t counterFontSize = 24;

   static constexpr std::array<std::string, 9> cellNumberTexture = {
         "emptyCell.png",
         "1.png",
         "2.png",
         "3.png",
         "4.png",
         "5.png",
         "6.png",
         "7.png",
         "8.png"
   };
};