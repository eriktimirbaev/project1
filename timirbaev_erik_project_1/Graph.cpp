#include "Graph.h"
#include <queue>
using namespace std;

Graph::Graph(const unordered_map<string, Edge>& edges, const set<string>& nodes, const unordered_map<string, Pipe>& pipes) : edges(edges) {
	int count = 0;
	for (string node : nodes) {
		this->nodes.insert({ count, node });
		count++;

	}
	SizeGraph = nodes.size();
	capacity.resize(SizeGraph, vector<double>(SizeGraph, 0.0));
	adj_weight.resize(SizeGraph, vector<int>(SizeGraph, 0.0));
	for (auto& [pipe_id, edge] : edges) {
		auto i = GetIndex(edge.start);
		auto j = GetIndex(edge.terminal);
		capacity[i][j] = pipes.at(pipe_id).GetCapacity();
		adj_weight[i][j] = pipes.at(pipe_id).GetLength();
	}
}

bool Graph::DFS_Cycle(int node, vector<bool>& visited, vector<bool>& recStack) {
	if (!visited[node]) {
		visited[node] = true;
		recStack[node] = true;

		for (int i = 0; i < SizeGraph; ++i) {
			if (adj_weight[node][i]) {
				if (!visited[i] && DFS_Cycle(i, visited, recStack)) { return true; }
				else if (recStack[i]) { return true; }
			}
		}
	}
	recStack[node] = false;
	return false;
}

bool Graph::HasCycle() {
	vector<bool> visited(SizeGraph, false);
	vector<bool> recStack(SizeGraph, false);

	for (int i = 0; i < SizeGraph; ++i) {
		if (DFS_Cycle(i, visited, recStack)) { return true; }
	}

	return false;
}

int Graph::GetIndex(string vertice) const
{
	for (auto& [index, node] : nodes) {
		if (node == vertice) { return index; }
	}
	return INT16_MAX;
}

bool Graph::Conteins(string Node) const
{
	for (auto& [index, node] : nodes) {
		if (node == Node) { return true; }
	}
	return false;
}

void Graph::DFS_Sort(int node, vector<bool>& visited, vector<string>& nodes) {
	visited[node] = true;

	for (int i = 0; i < SizeGraph; ++i) {
		if (adj_weight[node][i] && !visited[i]) {
			DFS_Sort(i, visited, nodes);
		}
	}

	nodes.push_back(this->nodes.at(node));
}

vector<string> Graph::TopologicalSort() {
	if (edges.empty()) {
		cout << endl << "The graph has no edges. Topological sort is not possible" << endl;
		return vector<string>();
	}
	else if (HasCycle()) {
		cout << endl << "There is a cycle in the graph. Topological sort is not possible" << endl;
		return vector<string>();
	}

	vector<bool> visited(SizeGraph, false);
	vector<string> result;

	for (int i = 0; i < SizeGraph; ++i) {
		if (!visited[i]) {
			DFS_Sort(i, visited, result);
		}
	}
	reverse(result.begin(), result.end());

	return result;
}