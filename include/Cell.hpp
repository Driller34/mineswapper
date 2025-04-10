#pragma once
#include <SFML/Graphics.hpp>

enum class CellState {HIDE, UNHIDE, FLAG};

class Cell
{
public:
    Cell();
    void setState(CellState state);
    CellState getState() const;
    void setNumber(const unsigned int number);
    void addBomb();
    unsigned int getNumber() const;
    void setBomb();
    bool isBomb() const;
    void reset();
private:
    bool _bomb{false};
    unsigned int _number{0};
    CellState _state{CellState::HIDE};
};