#include "pathfinder/utils.h"

std::vector<Position> GetSurroundingPositions(Position pos) {
    std::vector<Position> output;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (!(dy == 0 && dx == 0)) {
                output.push_back(Position(pos.x+dx, pos.y+dy));
            }
        }
    }

    return output;
}