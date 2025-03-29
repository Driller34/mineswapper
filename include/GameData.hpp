#pragma once
#include <SFML/Graphics.hpp>

struct GameData
{
   static constexpr unsigned int cellSize{30};
   static constexpr unsigned int rows{20};
   static constexpr unsigned int columns{20}; 
   static constexpr unsigned int mines{40};

   static constexpr unsigned int width{cellSize * columns};
   static constexpr unsigned int height{cellSize * rows};
};