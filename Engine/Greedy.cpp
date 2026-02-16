#include "Greedy.h"
#include <algorithm>
#include <limits>

Greedy::Greedy(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal) : graph(graph), start(start), goal(goal)
{
    for (auto& row : graph.getNodes()) {
        for (auto& node : row) {
            node->isVisited = false;
            node->parent = nullptr;
            node->distance = std::numeric_limits<float>::infinity();
        }
    }
    queue.push({ heuristic(*start, *goal), start });
}

float Greedy::heuristic(Node& a, Node& b) {
    return std::abs(a.position.x - b.position.x) + std::abs(a.position.y - b.position.y);
}

bool Greedy::step() {
    if (queue.empty() || finished)
        return false;

    std::shared_ptr<Node> current = queue.top().second;
    queue.pop();

    if (current->isVisited)
        return true;
    current->isVisited = true;

    if (current == goal) {
        finished = true;
        pathFound = true;
        return false;
    }

    for (std::shared_ptr<Node> neighbor : current->neighbors) {
        if (!neighbor->isWalkable || neighbor->isVisited)
            continue;

        neighbor->parent = current;

       
        float priority = heuristic(*neighbor, *goal);
        queue.push({ priority, neighbor });
    }

    if (queue.empty())
        finished = true;

    return true;
}

std::vector<std::shared_ptr<Node>> Greedy::getPath() {
    std::vector<std::shared_ptr<Node>> path;
    if (!pathFound)
        return path;

    std::shared_ptr<Node> current = goal;
    while (current != nullptr) {
        path.push_back(current);
        current = current->parent;
    }

    std::reverse(path.begin(), path.end());
    return path;
}


