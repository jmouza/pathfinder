#pragma once

/*
This file contains test grids, which will be converted to Grid objects.
S is a start node
F is a finish node
O is an obstacle node

For some grids, it also contains a vector of positions of the shortest path from start to finish.
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
    "S#O##\n"
    "##O##\n"
    "OOOF#\n";

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

static const std::string START_POINT_IN_THE_MIDDLE_STRAIGHT_LINE =
    "#####\n"
    "#####\n"
    "##S##\n"
    "#####\n"
    "##F##\n";

static const std::vector<Position> START_POINT_IN_THE_MIDDLE_STRAIGHT_LINE_POSITIONS = {
    Position(2,2), 
    Position(2,3), 
    Position(2,4)
};

static const std::string START_POINT_IN_THE_MIDDLE_LOOP =
    "O########FO\n"
    "O#OOOOOOO#O\n"
    "O#O#####O#O\n"
    "O#O#OOO#O#O\n"
    "O#O##SO#O#O\n"
    "O#OOOOO#O#O\n"
    "O#######O#O\n";

static const std::vector<Position> START_POINT_IN_THE_MIDDLE_LOOP_POSITIONS = {
    Position(5,4),
    Position(4,4),
    Position(3,4),
    Position(3,3),
    Position(3,2),
    Position(4,2),
    Position(5,2),
    Position(6,2),
    Position(7,2),
    Position(7,3),
    Position(7,4),
    Position(7,5),
    Position(7,6),
    Position(6,6),
    Position(5,6),
    Position(4,6),
    Position(3,6),
    Position(2,6),
    Position(1,6),
    Position(1,5),
    Position(1,4),
    Position(1,3),
    Position(1,2),
    Position(1,1),
    Position(1,0),
    Position(2,0),
    Position(3,0),
    Position(4,0),
    Position(5,0),
    Position(6,0),
    Position(7,0),
    Position(8,0),
    Position(9,0)
};

static const std::string GRID_WITH_ONE_NEIGHBOR =
    "###\n"
    "OSO\n"
    "#OF\n";

static const std::string GRID_WITH_TWO_NEIGHBORS =
    "###\n"
    "OS#\n"
    "#OF\n";

    static const std::string GRID_WITH_THREE_NEIGHBORS =
    "###\n"
    "OS#\n"
    "##F\n";
    
static const std::string GRID_WITH_NODE_SURROUNDED =
    "#O#\n"
    "OSO\n"
    "#OF\n";