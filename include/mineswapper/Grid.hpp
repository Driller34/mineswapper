#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

template<typename T>
class Grid
{
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

public:
    Grid(const size_t rows,
         const size_t columns)
        : _rows(rows),
        _columns(columns),
        _data(_rows * _columns){}
    
    inline size_t size() const { return _data.size(); }

    inline bool inBounds(const sf::Vector2i& position) const
    {
        return position.x >= 0 && position.y >= 0 && position.x < _columns && position.y < _rows;
    }

    inline T& at(const sf::Vector2i& position)
    {
        return _data[index(position)]; 
    }

    inline const T& at(const sf::Vector2i& position) const
    {
        return _data[index(position)];
    }

    inline T& operator[](const sf::Vector2i& position){ return _data[index(position)]; }

    inline const T& operator[](const sf::Vector2i& position) const 
    { 
        return _data[index(position)]; 
    }

    inline T& operator[](const size_t index){ return _data[index]; }

    inline const T& operator[](const size_t index) const { return _data[index]; }

    inline std::vector<T>& raw(){ return _data; }

    inline size_t index(const sf::Vector2i& position) const
    {
        return position.y * _columns + position.x;
    }

    const size_t rows() const { return _rows; }

    const size_t columns() const { return _columns; }

    iterator begin() { return _data.begin(); }
    iterator end() { return _data.end(); }

    const_iterator begin() const { return _data.begin(); }
    const_iterator end() const { return _data.end(); }

private:
    const size_t _rows;
    const size_t _columns;
    std::vector<T> _data;
};