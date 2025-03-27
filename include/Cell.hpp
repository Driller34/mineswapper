#pragma once
#include <SFML/Graphics.hpp>

enum class State {HIDE, UNHIDE, FLAG};

class Cell
{
public:
    Cell();
    void setState(State state);
    State getState() const;
    void setNumber(const unsigned int number);
    void addBomb();
    unsigned int getNumber() const;
    void setBomb();
    bool isBomb() const;
private:
    bool _bomb{false};
    unsigned int _number{0};
    State _state{State::HIDE};
};