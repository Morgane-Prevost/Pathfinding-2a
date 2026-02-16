#pragma once
#include "Graph.h"
#include <queue>
#include <vector>

struct CompareNode 
{
    bool operator()(const std::shared_ptr<Node> a, const std::shared_ptr<Node> b) const 
    {
        return a->fCost > b->fCost;
    }
};

class AStar 
{
private:
    Graph& graph;
    std::shared_ptr<Node> start;
    std::shared_ptr<Node> goal;
    bool finished = false;
    bool pathFound = false;

    float heuristic(std::shared_ptr<Node> a, std::shared_ptr<Node> b);
    float distance(std::shared_ptr<Node> a, std::shared_ptr<Node> b);

public:

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, CompareNode> openSet;

    AStar(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

    bool step();

    bool isFinished() const { return finished; }
    std::vector<std::shared_ptr<Node>> getPath();
};


