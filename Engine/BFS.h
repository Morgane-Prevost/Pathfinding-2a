#pragma once
#include "Graph.h"
#include <queue>

class BFS {
private:
    Graph& graph;
    std::shared_ptr<Node> start;
    std::shared_ptr<Node> goal;
    bool finished = false;
    bool pathFound = false;

public:
    std::queue<std::shared_ptr<Node>> queue;

    BFS(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

    bool step();                         
    bool isFinished() const { return finished; }

    std::vector<std::shared_ptr<Node>> getPath();
};


