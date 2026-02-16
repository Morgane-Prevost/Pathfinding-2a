#pragma once
#include "Node.h"

class Graph {
private: 
    std::vector<std::vector<std::shared_ptr<Node>>> nodes;
    int width, height;

public:

    Graph(int w, int h);
    void connectNodes();
    std::shared_ptr<Node> getNode(int x, int y);
    std::vector<std::vector<std::shared_ptr<Node>>>& getNodes();
};

