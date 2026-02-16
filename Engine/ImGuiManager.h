#pragma once
#include <vector>
#include <imgui.h>
#include <imgui-SFML.h>
#include "AlgoManager.h"

class ImGuiManager
{
private :

	bool bfsRunning = false;
	bool astarRunning = false;
	bool greedyRunning = false;
	bool dijkstraRunning = false;

	bool wantToll = true;
	bool done = true;

public :
	ImGuiManager();

	void displayImGui(Graph& graph, std::vector<std::shared_ptr<Node>>& path, std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

	bool getDone() const;
	bool getWantToll() const;
	bool getBfsRunning() const;
	bool getAstarRunning() const;
	bool getGreedyRunning() const;
	bool getDijkstraRunning() const;

	void setDone(bool value);
	void setWantToll(bool value);
	void setBfsRunning(bool value);
	void setAstarRunning(bool value);
	void setGreedyRunning(bool value);
	void setDijkstraRunning(bool value);
};

