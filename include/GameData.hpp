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