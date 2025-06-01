#pragma once

struct Position 
{
    unsigned int x;
    unsigned int y;

    Position(unsigned int x, unsigned int y): x(x), y(y) {}
    bool operator== (const Position &other) const {return this->x == other.x && this->y == other.y;}
};