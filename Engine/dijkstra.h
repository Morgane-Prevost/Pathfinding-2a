#pragma once
#include "Graph.h"
#include <queue>
#include <vector>
#include <functional>

class Dijkstra {
private:
    Graph& graph;
    std::shared_ptr<Node> start;
    std::shared_ptr<Node> goal;
    bool finished = false;
    bool pathFound = false;

public:
    std::priority_queue<std::pair<float, std::shared_ptr<Node>>, std::vector<std::pair<float, std::shared_ptr<Node>>>, std::greater<>> queue;
    Dijkstra(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

    bool step();
    std::vector<std::shared_ptr<Node>> getPath();
    bool isFinished() const { return finished; }

};
