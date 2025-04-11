#include "Cell.hpp"

Cell::Cell()
{
    
}

void Cell::reset()
{
    _state = CellState::HIDE;
    _mine = false;
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

void Cell::setMine()
{
    _mine = true;
}

bool Cell::isMine() const
{
    return _mine;
}

void Cell::addMine()
{
    _number++;
}

