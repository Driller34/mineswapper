#pragma once
#include <SFML/Graphics.hpp>

struct GameData
{
   static constexpr unsigned int width{800};
   static constexpr unsigned int height{800};
   static constexpr unsigned int cellSize{20};
   static constexpr unsigned int rows{20};
   static constexpr unsigned int columns{20}; 
   static constexpr unsigned int mines{20};
};