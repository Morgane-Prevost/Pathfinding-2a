#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Node 
{
    sf::Vector2f position;
    bool isWalkable = true;
    bool isToll = false;
    bool isVisited = false; 
    std::shared_ptr<Node> parent = nullptr;
    std::vector<std::shared_ptr<Node>> neighbors;

    // ASTAR
    float gCost = INFINITY;
    float hCost = 0.0f;
    float fCost = INFINITY;

    // DIJKSTRA
    float cost = 1.0f; 
    float distance = INFINITY;

    Node(int x, int y);
    void addNeighbor(std::shared_ptr<Node> neighbor);
};

