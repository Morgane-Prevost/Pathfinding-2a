#include "ImGuiManager.h"


ImGuiManager::ImGuiManager() {}

void ImGuiManager::displayImGui(Graph& graph, std::vector<std::shared_ptr<Node>>& path, std::shared_ptr<Node> start, std::shared_ptr<Node> goal)
{
    ImGui::Begin("Pathfinding Controls");

    if (ImGui::Button("Start BFS")) 
    {
        bfsRunning = true;
        algoManager->resetAlgo(Algo::BFS, graph, start, goal);
    }
    ImGui::Text("BFS running: %s", bfsRunning ? "Yes" : "No");

    if (ImGui::Button("Start Greedy")) 
    {
        greedyRunning = true;
        algoManager->resetAlgo(Algo::GREEDY, graph, start, goal);
    }
    ImGui::Text("Greedy running: %s", greedyRunning ? "Yes" : "No");

    if (ImGui::Button("Start Dijkstra")) 
    {
        dijkstraRunning = true;
        algoManager->resetAlgo(Algo::DIJKSTRA, graph, start, goal);
    }
    ImGui::Text("Dijkstra running: %s", dijkstraRunning ? "Yes" : "No");

    if (ImGui::Button("Start Astar")) 
    {
        astarRunning = true;
        algoManager->resetAlgo(Algo::ASTAR, graph, start, goal);
    }
    ImGui::Text("Astar running: %s", astarRunning ? "Yes" : "No");

    if (ImGui::Button("Reset") && !bfsRunning && !greedyRunning && !dijkstraRunning && !astarRunning) 
    {
        algoManager->setNodeVisited(0);
        algoManager->setEstimatedTime(0);
        algoManager->setDistance(0);
        algoManager->setTotalPrice(0);

        path.clear();
        for (auto row : graph.getNodes())
        {
            for (auto node : row)
            {
                node->isVisited = false, node->parent = nullptr, node->distance = INFINITY;
            }
        } 
    }
    ImGui::End();

    ImGui::Begin("Pathfinding Stats");

    ImGui::Text("Node visited: %d", (int)algoManager->getNodeVisited());
    ImGui::Text("Estimated time: %.2f h", (float)algoManager->getEstimatedTime());
    ImGui::Text("Distance: %.1f km", (float)algoManager->getDistance());
    ImGui::Text("Total Price: %.2f euros", (float)algoManager->getTotalPrice());
    ImGui::Text(" ");

    if (ImGui::Button("Toggle"))
    {
        if (wantToll)
        {
            wantToll = false;
        }
        else
        {
            wantToll = true;
        }
    }
    ImGui::Text("Ignore tolls: %s", wantToll ? "Yes" : "No");

    ImGui::End();
}

bool ImGuiManager::getDone() const { return done; }
bool ImGuiManager::getWantToll() const { return wantToll; }
bool ImGuiManager::getBfsRunning() const { return bfsRunning; }
bool ImGuiManager::getAstarRunning() const { return astarRunning; }
bool ImGuiManager::getGreedyRunning() const { return greedyRunning; }
bool ImGuiManager::getDijkstraRunning() const { return dijkstraRunning; }

void ImGuiManager::setDone(bool value) { done = value; }
void ImGuiManager::setWantToll(bool value) { wantToll = value; }
void ImGuiManager::setBfsRunning(bool value) { bfsRunning = value; }
void ImGuiManager::setAstarRunning(bool value) { astarRunning = value; }
void ImGuiManager::setGreedyRunning(bool value) { greedyRunning = value; }
void ImGuiManager::setDijkstraRunning(bool value) { dijkstraRunning = value; }


