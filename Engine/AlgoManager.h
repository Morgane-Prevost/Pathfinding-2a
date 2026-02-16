#pragma once
#include "BFS.h"
#include "Dijkstra.h"
#include "Greedy.h"
#include "Astar.h"

enum class Algo
{
	BFS,
	GREEDY,
	DIJKSTRA,
	ASTAR
};

class AlgoManager
{
private:

	static AlgoManager* instance;
	AlgoManager() {}

	std::shared_ptr<BFS> bfs;
	std::shared_ptr<Greedy> greedy;
	std::shared_ptr<Dijkstra> dijkstra;
	std::shared_ptr<AStar> aStar;

	const int tollPrice = 8;
	float totalPrice = 0;
	bool done = false;

	int nodeVisited = 0;
	float estimatedTime = 0;
	float distance = 0;
	bool algoIsFinished = false;

public:

	static AlgoManager* getInstance();

	~AlgoManager();

	void makeAlgo(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

	void resetAlgo(Algo algo, Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal);

	void checkCost(std::vector<std::shared_ptr<Node>>& path);
	bool updateAlgo(Algo algo, std::vector<std::shared_ptr<Node>>& path, int dBetweenN, int km_h);
	void finishAlgo(std::vector<std::shared_ptr<Node>>& path, int dBetweenN, int km_h);

#pragma region Getters

	BFS& getBfs();
	Greedy& getGreedy();
	Dijkstra& getDijkstra();
	AStar& getAstar();

	int getTollPrice() const;
	float getTotalPrice() const;

	int getNodeVisited() const;
	float getEstimatedTime() const;
	float getDistance() const;
	bool getAlgoIsFinished() const;

#pragma endregion

#pragma region Setters

	void setTotalPrice(float price);

	void setNodeVisited(int nodes);
	void setEstimatedTime(float time);
	void setDistance(float dist);
	void setAlgoIsFinished(bool value);

#pragma endregion
};

extern AlgoManager* algoManager;

