#include <SFML/Graphics.hpp>
#include <iostream>
#include "Graph.h"
#include "ImGuiManager.h"

const int cols = 20, rows = 15;
const int cellSize = 40;
Graph graph(cols, rows);
std::shared_ptr<Node> start = graph.getNode(2, 2);
std::shared_ptr<Node> goal = graph.getNode(17, 10);

void switchState(std::string type, int x, int y);

int main() {
    sf::RenderWindow window(sf::VideoMode({ 1080, 640 }), "BFS + ImGui Visualizer");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    int distanceOfEdges = 50;
    int km_h = 70;

    ImGuiManager igManager;

    std::vector<std::shared_ptr<Node>> path;

    algoManager->makeAlgo(graph, start, goal);

    sf::Clock deltaClock;

    while (window.isOpen()) 
    {
        sf::Vector2f mousePos = { float(sf::Mouse::getPosition(window).x), float(sf::Mouse::getPosition(window).y) };

        while (const auto event = window.pollEvent()) 
        {
            ImGui::SFML::ProcessEvent(window, *event);

            if (event->is<sf::Event::Closed>()) 
            {
                window.close();
            }
#pragma region Inputs

            if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            {
                switchState("Walkable", mousePos.x / cellSize, mousePos.y / cellSize);
            }

            if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T))
            {
                switchState("Toll", mousePos.x / cellSize, mousePos.y / cellSize);
            }

            if (event->is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            {
                start = graph.getNode(mousePos.x / cellSize, mousePos.y / cellSize);
            }

            if (event->is<sf::Event::MouseButtonPressed>() && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                goal = graph.getNode(mousePos.x / cellSize, mousePos.y / cellSize);
            }
        }

#pragma endregion

        ImGui::SFML::Update(window, deltaClock.restart());

        igManager.displayImGui(graph, path, start, goal);

        if (igManager.getAstarRunning())
        {
            if (!algoManager->updateAlgo(Algo::ASTAR, path, distanceOfEdges, km_h))
            {
                igManager.setAstarRunning(false);
            }
        }
        if (igManager.getBfsRunning())
        {
            if (!algoManager->updateAlgo(Algo::BFS, path, distanceOfEdges, km_h))
            {
                igManager.setBfsRunning(false);
            }
        }
        if (igManager.getDijkstraRunning())
        {
            if (!algoManager->updateAlgo(Algo::DIJKSTRA, path, distanceOfEdges, km_h))
            {
                igManager.setDijkstraRunning(false);
            }
        }
        if (igManager.getGreedyRunning())
        {
            if (!algoManager->updateAlgo(Algo::GREEDY, path, distanceOfEdges, km_h))
            {
                igManager.setGreedyRunning(false);
            }
        }

        if (igManager.getWantToll() && !igManager.getDone())
        {
            for (auto row : graph.getNodes())
            {
                for (auto node : row)
                {
                    if (node->isToll) 
                    {
                        node->isWalkable = true;
                    }
                }
            }
            igManager.setDone(true);
        }
        else if (!igManager.getDone())
        {

            for (auto row : graph.getNodes())
            {
                for (auto node : row)
                {
                    if (node->isToll)
                    {
                        node->isWalkable = false;
                    }
                }
            }
            igManager.setDone(true);
        }

        window.clear(sf::Color::Black);
        ImGui::SFML::Render(window);
        for (auto& row : graph.getNodes()) 
        {
            for (auto& node : row) 
            {
                sf::RectangleShape rect(sf::Vector2f(cellSize - 2, cellSize - 2));
                rect.setPosition({ static_cast<float>(node->position.x * cellSize),
                                   static_cast<float>(node->position.y * cellSize) });

                if (node == start)
                    rect.setFillColor(sf::Color::Green);
                else if (node == goal)
                    rect.setFillColor(sf::Color::Red);
                else if (std::find(path.begin(), path.end(), node) != path.end() && !node->isToll)
                    rect.setFillColor(sf::Color::Yellow);
                else if (node->isVisited && !node->isToll)
                    rect.setFillColor(sf::Color(sf::Color::Blue));
                else if (!node->isWalkable && !node->isToll)
                    rect.setFillColor(sf::Color(sf::Color::Black));
                else if (node->isToll)
                    rect.setFillColor(sf::Color(sf::Color::White));
                else
                    rect.setFillColor(sf::Color(50, 50, 50));

                window.draw(rect);
            }
        }

        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}

void switchState(std::string type, int x, int y)
{
    std::shared_ptr<Node> selectedNode = graph.getNode(x, y);

    if (selectedNode != start and selectedNode != goal)
    {
        if (type == "Walkable" && !selectedNode->isToll)
        {
            if (selectedNode->isWalkable) selectedNode->isWalkable = false;
            else selectedNode->isWalkable = false;

        }
        if (type == "Toll")
        {
            if (selectedNode->isToll) selectedNode->isToll = false;
            else selectedNode->isToll = false;
        }
    }
}

