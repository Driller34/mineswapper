#pragma once
#include "utils.hpp"

struct GameSettings 
{
    size_t rows;
    size_t columns;
    size_t mines;

    size_t width() const { return columns * conf::cellSize; }
    size_t height() const { return rows * conf::cellSize + conf::panelHeight(); }
};
