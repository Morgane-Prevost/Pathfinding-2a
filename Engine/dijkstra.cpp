#include "Dijkstra.h"
#include <algorithm>

Dijkstra::Dijkstra(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal) : graph(graph), start(start), goal(goal) {

    for (auto& row : graph.getNodes())
        for (auto& node : row) {
            node->isVisited = false;
            node->parent = nullptr;
            node->distance = INFINITY;
        }

    start->distance = 0.0f;
    queue.push({ 0.0f, start });
}

bool Dijkstra::step() {
    if (queue.empty() || finished)
        return false;

    std::shared_ptr<Node> current = queue.top().second;
    queue.pop();

    if (current->isVisited) return true;
    current->isVisited = true;

    if (current == goal) {
        finished = true;
        pathFound = true;
        return false;
    }

    for (std::shared_ptr<Node> neighbor : current->neighbors) {
        if (!neighbor->isWalkable) continue;

        float newDist = current->distance + neighbor->cost;

        if (newDist < neighbor->distance) {
            neighbor->distance = newDist;
            neighbor->parent = current;
            queue.push({ newDist, neighbor });
        }
    }

    if (queue.empty()) finished = true;
    return true;
}

std::vector<std::shared_ptr<Node>> Dijkstra::getPath() {
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
