#include <queue>
#include <vector>

#include "pathfinder/bfs.h"

const Result BFS::Execute(const Grid grid) const {
    Result result;

    std::queue<Node> queue;
    std::queue<std::vector<Node>> paths;
    SetOfNodes explored;

    queue.push(grid.GetStartNode());
    paths.push({});
    explored.insert(grid.GetStartNode());

    while (!queue.empty()) {
        result.explored_steps.push_back(explored); 

        Node node = queue.front();
        queue.pop();

        auto path = paths.front(); 
        paths.pop();
        path.push_back(node);

        if (node == grid.GetFinishNode()) {
            result.found_path = true;
            result.path = path;
            return result;
        }

        for (const auto adj_node: grid.GetNeighbours(node)) {
            if (!IsExplored(*adj_node, explored) && !IsObstacle(*adj_node)) {
                explored.insert(*adj_node);
                queue.push(*adj_node);
                paths.push(path);
            }
        }
    }

    return result;
}

bool BFS::IsExplored(const Node node, const std::unordered_set<Node, Node::HashFunction> explored_set) const {
    return (explored_set.count(node) != 0);
}

bool BFS::IsObstacle(const Node node) const {
    return node.GetNodeType() == NodeType::Obstacle;
}
