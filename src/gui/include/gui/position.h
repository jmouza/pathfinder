#pragma once

#include <cstddef>
#include <stdexcept>

struct Position 
{
    int x;
    int y;

    Position(int x_, int y_): x(x_), y(y_) {}
    bool operator== (const Position &other) const {return this->x == other.x && this->y == other.y;}
    bool operator!= (const Position &other) const {return this->x != other.x || this->y != other.y;}    

    struct HashFunction
    {
        size_t operator()(const Position& position) const
        {
        size_t x_hash = std::hash<int>()(position.x);
        size_t y_hash = std::hash<int>()(position.y) << 1;
        
        return x_hash ^ y_hash;
        }
    };
};