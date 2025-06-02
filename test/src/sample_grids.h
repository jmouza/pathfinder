/*
This file contains test grids, which will be converted to Grid objects.
S is a start node
F is a finish node
*/

#include <string>

static const std::string HORIZONTAL_PATH =
    "S########F\n"
    "##########\n"
    "##########\n"
    "##########\n"
    "##########\n";

static const std::string VERTIAL_PATH =
    "#########S\n"
    "##########\n"
    "##########\n"
    "##########\n"
    "#########F\n";

static const std::string DIAGONAL_PATH =
    "####F\n"
    "#####\n"
    "#####\n"
    "#####\n"
    "S####\n";