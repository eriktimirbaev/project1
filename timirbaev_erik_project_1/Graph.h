#pragma once
#include "Utilities.h"
#include "Pipe.h"
#include <map>
#include <unordered_map>
#include <set>

class Graph;
class GTS;
class Connections;

class Edge
{
	friend Graph;
	friend GTS;
	friend Connections;

public:
	Edge() {};

private:
	std::string start, terminal, pipe_id;
	Edge(std::string start, std::string terminal, std::string pipe_id) : start(start), terminal(terminal), pipe_id(pipe_id) {};
};

class Graph
{
	friend GTS;
public:
	Graph(const std::unordered_map<std::string, Edge>& edges, const std::set<std::string>& nodes, const std::unordered_map<std::string, Pipe>& pipes);
	std::vector<std::string> TopologicalSort();

private:
	bool DFS_Cycle(int, std::vector<bool>&, std::vector<bool>&);
	void DFS_Sort(int v, std::vector<bool>& visited, std::vector<std::string>& nodes);
	bool HasCycle();
	int GetIndex(std::string node) const;
	bool Conteins(std::string Node) const;
	std::map<int, std::string> nodes;
	std::unordered_map<std::string, Edge> edges;
	std::vector<std::vector<double>> capacity;
	std::vector<std::vector<int>> adj_weight;
	int SizeGraph;
};