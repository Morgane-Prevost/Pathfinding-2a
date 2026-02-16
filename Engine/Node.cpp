#include "Node.h"

Node::Node(int x, int y) : position(x, y) {}

void Node::addNeighbor(std::shared_ptr<Node> neighbor) { neighbors.push_back(neighbor); }
