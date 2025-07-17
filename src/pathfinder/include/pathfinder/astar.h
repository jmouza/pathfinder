#pragma once

#include "pathfinder/pathfinder_algorithm.h"

class AStar : public PathfinderAlgorithm
{
public:
    AStar(): PathfinderAlgorithm() {};
    const PathfinderResult Execute() override;

private:
    int DistanceBetweenNodes(Node source, Node target) const;
    void ConstructPath();
};