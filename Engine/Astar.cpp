#include "AStar.h"
#include <algorithm>
#include <queue>
#include <cmath>

AStar::AStar(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal) : graph(graph), start(start), goal(goal) 
{
    for (auto& row : graph.getNodes())
        for (auto& node : row) {
            node->isVisited = false;
            node->parent = nullptr;
            node->gCost = INFINITY;
            node->hCost = 0.0f;
            node->fCost = INFINITY;
        }

    start->gCost = 0.0f;
    start->hCost = heuristic(start, goal);
    start->fCost = start->hCost;

    openSet.push(start);
}

float AStar::heuristic(std::shared_ptr<Node> a, std::shared_ptr<Node> b) 
{
    
    return std::abs(a->position.x - b->position.x) + std::abs(a->position.y - b->position.y);
}

float AStar::distance(std::shared_ptr<Node> a, std::shared_ptr<Node> b) 
{
    return std::sqrt((a->position.x - b->position.x) * (a->position.x - b->position.x) +
        (a->position.y - b->position.y) * (a->position.y - b->position.y));
}

bool AStar::step() 
{
    if (openSet.empty() || finished)
        return false;

    std::shared_ptr<Node> current = openSet.top();
    openSet.pop();

    if (current == goal) {
        finished = true;
        pathFound = true;
        return false;
    }

    current->isVisited = true;

    for (std::shared_ptr<Node> neighbor : current->neighbors) {
        if (!neighbor->isWalkable || neighbor->isVisited)
            continue;

        float tentativeG = current->gCost + distance(current, neighbor);

        if (tentativeG < neighbor->gCost) {
            neighbor->parent = current;
            neighbor->gCost = tentativeG;
            neighbor->hCost = heuristic(neighbor, goal);
            neighbor->fCost = neighbor->gCost + neighbor->hCost;

            openSet.push(neighbor);
        }
    }

    if (openSet.empty()) finished = true;
    return true;
}

std::vector<std::shared_ptr<Node>> AStar::getPath() {
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

