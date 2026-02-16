#include "Graph.h"

Graph::Graph(int w, int h) : width(w), height(h) {
    nodes.reserve(height);
    for (int y = 0; y < height; ++y) 
    {
        nodes.emplace_back();
        nodes[y].reserve(width);
        for (int x = 0; x < width; ++x) 
        {
            nodes[y].emplace_back(std::make_shared<Node>(x, y));
        }
    }
    connectNodes();
}
void Graph::connectNodes() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::shared_ptr<Node> n = nodes[y][x];
            n->neighbors.clear();

            if (x > 0) n->addNeighbor(nodes[y][x - 1]);
            if (x < width - 1) n->addNeighbor(nodes[y][x + 1]);
            if (y > 0) n->addNeighbor(nodes[y - 1][x]);
            if (y < height - 1) n->addNeighbor(nodes[y + 1][x]);
        }
    }
}


std::shared_ptr<Node> Graph::getNode(int x, int y) {
    if (x < 0 || y < 0 || x >= width || y >= height)
        return nullptr;
    return nodes[y][x];
}

std::vector<std::vector<std::shared_ptr<Node>>>& Graph::getNodes()
{
    return nodes;
}

