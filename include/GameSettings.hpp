#pragma once
#include "utils.hpp"

struct GameSettings 
{
    size_t rows;
    size_t columns;
    size_t mines;

    unsigned int width() const { return columns * conf::cellSize; }
    unsigned int height() const { return rows * conf::cellSize + conf::panelHeight(); }
};
