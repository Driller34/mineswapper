#include "Cell.hpp"

Cell::Cell()
{
    
}

void Cell::reset()
{
    _state = CellState::HIDE;
    _bomb = false;
    _number = 0;
}

void Cell::setState(CellState state)
{
    _state = state;
}

CellState Cell::getState() const
{
    return _state;
}

void Cell::setNumber(const unsigned int number)
{
    _number = number;
}

unsigned int Cell::getNumber() const
{
    return _number;
}

void Cell::setBomb()
{
    _bomb = true;
}

bool Cell::isBomb() const
{
    return _bomb;
}

void Cell::addBomb()
{
    _number++;
}

