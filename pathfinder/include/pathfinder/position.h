#pragma once

#include <cstddef>
#include <stdexcept>

/* Represents a positive position. */
struct Position 
{
    int x;
    int y;

    Position(int x_, int y_): x(x_), y(y_) {}
    bool operator== (const Position &other) const {return this->x == other.x && this->y == other.y;}
    bool operator!= (const Position &other) const {return this->x != other.x || this->y != other.y;}    
};