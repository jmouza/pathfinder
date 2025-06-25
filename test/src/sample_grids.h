#pragma once

/*
This file contains test grids, which will be converted to Grid objects.
S is a start node
F is a finish node
O is an obstacle node

For each grid, it also contains a vector of positions of the shortest path from start to finish.
*/

#include <string>
#include <vector>

#include "pathfinder/position.h"

static const std::string MINI_GRID =
    "S#F\n"
    "###\n";

static const std::vector<Position> MINI_GRID_PATH_POSITIONS = {
    Position(0, 0),
    Position(1, 0),
    Position(2, 0)
};

static const std::string HORIZONTAL_PATH =
    "S########F\n"
    "##########\n"
    "##########\n"
    "##########\n"
    "OOOOOOOOOO\n";

static const std::vector<Position> HORIZONTAL_PATH_POSITIONS = {
    Position(0, 0),
    Position(1, 0),
    Position(2, 0),
    Position(3, 0),
    Position(4, 0),
    Position(5, 0),
    Position(6, 0),
    Position(7, 0),
    Position(8, 0),
    Position(9, 0)
};

static const std::string VERTICAL_PATH =
    "#########S\n"
    "##########\n"
    "##########\n"
    "##########\n"
    "#########F\n";

static const std::vector<Position> VERTICAL_PATH_POSITIONS = {
    Position(9, 0),
    Position(9, 1),
    Position(9, 2),
    Position(9, 3),
    Position(9, 4)
};

static const std::string SHORT_PATH =
    "##########\n"
    "###SF#####\n"
    "##########\n"
    "##########\n"
    "##########\n";

static const std::vector<Position> SHORT_PATH_POSITIONS = {
    Position(3, 1),
    Position(4, 1)
};

static const std::string IMPOSSIBLE_PATH1 =
    "S#O#######\n"
    "##O#######\n"
    "OOO#######\n"
    "##########\n"
    "#########F\n";

static const std::string IMPOSSIBLE_PATH2 =
    "S######O##\n"
    "#######O##\n"
    "#######O##\n"
    "#######O##\n"
    "#######O#F\n";

static const std::string IMPOSSIBLE_PATH3 =
    "SO########\n"
    "OF########\n"
    "##########\n"
    "##########\n"
    "##########\n";

static const std::string PATH_WITH_OBSTACLES1 =
    "SOOOOOOOOF\n"
    "#OOOOOOOO#\n"
    "#OOOOOOOO#\n"
    "#OOOOOOOO#\n"
    "##########\n";

static const std::vector<Position> PATH_WITH_OBSTACLES1_POSITIONS = {
    Position(0, 0),
    Position(0, 1),
    Position(0, 2),
    Position(0, 3),
    Position(0, 4),
    Position(1, 4),
    Position(2, 4),
    Position(3, 4),
    Position(4, 4),
    Position(5, 4),
    Position(6, 4),
    Position(7, 4),
    Position(8, 4),
    Position(9, 4),
    Position(9, 3),
    Position(9, 2),
    Position(9, 1),
    Position(9, 0)
};

static const std::string PATH_WITH_OBSTACLES2 =
    "####S#####\n"
    "###OO#####\n"
    "####O#####\n"
    "####F#####\n"
    "##########\n";

static const std::vector<Position> PATH_WITH_OBSTACLES2_POSITIONS = {
    Position(4, 0),
    Position(5, 0),
    Position(5, 1),
    Position(5, 2),
    Position(5, 3),
    Position(4, 3),
};

static const std::string DIAGONAL_PATH1 =
    "S###\n"
    "####\n"
    "####\n"
    "###F\n";

static const std::string DIAGONAL_PATH2 =
    "S#OO\n"
    "O##O\n"
    "#O##\n"
    "##OF\n";

static const std::vector<Position> DIAGONAL_PATH2_POSITIONS = {
    Position(0,0), 
    Position(1,0), 
    Position(1,1), 
    Position(2,1), 
    Position(2,2), 
    Position(3,2), 
    Position(3,3)
};