#pragma once

#include <cstddef>
#include <stdexcept>

/* Represents a positive position. */
struct Position 
{
    int x;
    int y;

    Position(int x_, int y_){
        if (x_ < 0 || y_ < 0) throw std::invalid_argument("Negative position.");
        x = x_;
        y = y_;
    }
    bool operator== (const Position &other) const {return this->x == other.x && this->y == other.y;}
    
};