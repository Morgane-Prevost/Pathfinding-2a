#include "AlgoManager.h"

AlgoManager* AlgoManager::getInstance()
{
	if (instance == nullptr) 
	{ 
		instance = new AlgoManager();
	}
	return instance;
}

AlgoManager::~AlgoManager()
{
	bfs.reset();
	greedy.reset();
	dijkstra.reset();
	aStar.reset();
}

void AlgoManager::makeAlgo(Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal)
{
	bfs = std::make_shared<BFS>(graph, start, goal);
	greedy = std::make_shared<Greedy>(graph, start, goal);
	dijkstra = std::make_shared<Dijkstra>(graph, start, goal);
	aStar = std::make_shared<AStar>(graph, start, goal);
}

void AlgoManager::resetAlgo(Algo algo, Graph& graph, std::shared_ptr<Node> start, std::shared_ptr<Node> goal)
{
	switch (algo)
	{
	case Algo::BFS:
		bfs.reset(new BFS(graph, start, goal));
		break;

	case Algo::GREEDY:
		greedy.reset(new Greedy(graph, start, goal));
		break;

	case Algo::DIJKSTRA:
		dijkstra.reset(new Dijkstra(graph, start, goal));
		break;

	case Algo::ASTAR:
		aStar.reset(new AStar(graph, start, goal));
		break;
	}
}

void AlgoManager::checkCost(std::vector<std::shared_ptr<Node>>& path)
{
	int start = 0;
	int end = 0;
	for (int i = 0; i < path.size(); i++)
	{
		std::shared_ptr<Node> node = path[i];
		if (node->isToll)
		{
			if (start != 0)
			{
				end = i;
			}
			else
			{
				start = i;
			}
		}
		if (end != 0)
		{
			int dBetweenT = end - start;
			totalPrice += tollPrice * dBetweenT;
			int start = 0;
			int end = 0;
		}
	}
}

bool AlgoManager::updateAlgo(Algo algo, std::vector<std::shared_ptr<Node>>& path, int dBetweenN, int km_h)
{
	switch (algo)
	{
	case Algo::BFS:
		
		bfs->step();
		if (bfs->isFinished())
		{
			path = bfs->getPath();
			finishAlgo(path, dBetweenN, km_h);
			return false;
		}
		break;

	case Algo::GREEDY:
		greedy->step();
		if (greedy->isFinished())
		{
			path = greedy->getPath();
			finishAlgo(path, dBetweenN, km_h);
			return false;
		}
		break;

	case Algo::DIJKSTRA:
		dijkstra->step();
		if (dijkstra->isFinished())
		{
			path = dijkstra->getPath();
			finishAlgo(path, dBetweenN, km_h);
			return false;
		}
		break;

	case Algo::ASTAR:
		aStar->step();
		if (aStar->isFinished())
		{
			path = aStar->getPath();
			finishAlgo(path, dBetweenN, km_h);
			return false;
		}
		break;
	}

	nodeVisited++;
	return true;
}

void AlgoManager::finishAlgo(std::vector<std::shared_ptr<Node>>& path, int dBetweenN, int km_h)
{
	estimatedTime = dBetweenN * path.size() / km_h;
	distance = dBetweenN * path.size();
	checkCost(path);
	totalPrice /= dBetweenN;
}

#pragma region Getters

BFS& AlgoManager::getBfs() { return *bfs; }
Greedy& AlgoManager::getGreedy() { return *greedy; }
Dijkstra& AlgoManager::getDijkstra() { return *dijkstra; }
AStar& AlgoManager::getAstar() { return *aStar; }

int AlgoManager::getTollPrice() const { return tollPrice; }
float AlgoManager::getTotalPrice() const { return totalPrice; }

int AlgoManager::getNodeVisited() const { return nodeVisited; }
float AlgoManager::getEstimatedTime() const { return estimatedTime; }
float AlgoManager::getDistance() const { return distance; }
bool AlgoManager::getAlgoIsFinished() const { return algoIsFinished; }

#pragma endregion

#pragma region Setters

void AlgoManager::setTotalPrice(float price) { totalPrice = price; }

void AlgoManager::setNodeVisited(int nodes) { nodeVisited = nodes; }
void AlgoManager::setEstimatedTime(float time) { estimatedTime = time; }
void AlgoManager::setDistance(float dist) { distance = dist; }
void AlgoManager::setAlgoIsFinished(bool value) { algoIsFinished = value; }

#pragma endregion

AlgoManager* AlgoManager::instance = nullptr;
AlgoManager* algoManager = AlgoManager::getInstance();
