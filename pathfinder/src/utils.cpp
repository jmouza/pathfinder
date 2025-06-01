#include "pathfinder/utils.h"

std::vector<Position> GetSurroundingPositions(Position pos, int nr_rows, int nr_cols) {
    std::vector<Position> output;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dy == 0 && dx == 0) continue;

            if ((pos.x+dx)>=0 && (pos.y+dy)>=0 && (pos.x+dx) < nr_cols && (pos.y+dy) < nr_rows) {
                output.push_back(Position(pos.x+dx, pos.y+dy));
            }
        }
    }

    return output;
}