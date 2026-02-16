#pragma once
#include <vector>
#include <queue>
#include <cmath>
#include "Graph.h"

class Greedy {
private:
    Graph& graph;
    std::shared_ptr<Node> start;
    std::shared_ptr<Node> goal;

    bool finished = false;
    bool pathFound = false;

    float heuristic(Node& a, Node& b);

public:
    Greedy(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

    bool step();
    std::vector<std::shared_ptr<Node>> getPath(); 
    bool isFinished() const { return finished; }
    bool hasFoundPath() const { return pathFound; }

    std::priority_queue<std::pair<float, std::shared_ptr<Node>>, std::vector<std::pair<float, std::shared_ptr<Node>>>, std::greater<std::pair<float, std::shared_ptr<Node>>>> queue;
};

