#include "BFS.h"
#include <algorithm>

BFS::BFS(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal) : graph(graph), start(start), goal(goal)
{

    for (auto& row : graph.getNodes())
        for (auto& node : row)
            node->isVisited = false, node->parent = nullptr;

    start->isVisited = true;
    queue.push(start);
}

bool BFS::step() {
    if (queue.empty() || finished)
        return false;

    std::shared_ptr<Node> current = queue.front();
    queue.pop();

    if (current == goal) {
        finished = true;
        pathFound = true;
        return false;
    }

    for (std::shared_ptr<Node> neighbor : current->neighbors) {
        if (!neighbor->isVisited && neighbor->isWalkable) {
            neighbor->isVisited = true;
            neighbor->parent = current;
            queue.push(neighbor);
        }
    }

    if (queue.empty()) finished = true;
    return true;
}

std::vector<std::shared_ptr<Node>> BFS::getPath() {
    std::vector<std::shared_ptr<Node>> path;
    if (!pathFound) return path;

    std::shared_ptr<Node> current = goal;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}
