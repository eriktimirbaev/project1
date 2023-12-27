#include "Graph.h"
#include <queue>
using namespace std;

ofstream& operator << (ofstream& file, const Edge& edge) {
	if (file.is_open()) {
		file << edge.pipe_id << " ";
		file << edge.start << " ";
		file << edge.terminal << endl;
	}
	return file;
}
ifstream& operator >> (ifstream& file, Edge& edge) {
	if (file.is_open()) {
		file >> edge.pipe_id;
		file >> edge.start;
		file >> edge.terminal;
	}
	return file;
}

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

vector<string> Graph::Metod_Deikstra(int StartNode, int EndNode) const {
	if (edges.empty()) {
		cout << endl << "The graph has no edges. It is impossible to find the shortest path" << endl;
		return vector<string>();
	}
	else if (!Conteins(int_to_string(StartNode)) && !Conteins(int_to_string(EndNode))) {
		cout << endl << "There are no stations with this ID in the graph. It is impossible to find the shortest path" << endl;
		return vector<string>();
	}
	vector<int> dist(SizeGraph, INT_MAX);
	vector<int> prev(SizeGraph, -1);
	vector<bool> visited(SizeGraph, false);

	StartNode = GetIndex(int_to_string(StartNode));
	EndNode = GetIndex(int_to_string(EndNode));

	dist[StartNode] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, StartNode });

	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();

		if (u == EndNode) { break; }

		visited[u] = true;

		for (int v = 0; v < SizeGraph; ++v) {
			if (!visited[v] && adj_weight[u][v] && dist[u] != INT_MAX &&
				dist[u] + adj_weight[u][v] < dist[v])
			{
				dist[v] = dist[u] + adj_weight[u][v];
				prev[v] = u;
				pq.push({ dist[v], v });
			}
		}
	}

	vector<string> path;
	int current_node = EndNode;
	while (current_node != StartNode) {
		path.push_back(nodes.at(current_node));
		if (prev[current_node] != -1) {
			current_node = prev[current_node];
		}
		else {
			cout << "There is no path between the specified vertices" << endl;
			return vector<string>();
		}
	}
	path.push_back(nodes.at(StartNode));
	reverse(path.begin(), path.end());

	return path;
}

double Graph::Lenght_ShortestPath(std::vector<string>& path)
{
	double length = 0.0;
	if (path.size() < 2) { return length; }

	for (size_t i = 0; i < path.size() - 1; ++i) {
		int start = GetIndex(path[i]);
		int end = GetIndex(path[i + 1]);

		if (start >= SizeGraph || end >= SizeGraph || !adj_weight[start][end]) {
			cout << "There is no edge between the specified vertices" << endl;
			return INT64_MAX;
		}
		length += adj_weight[start][end];
	}
	return length;
}

bool Graph::BFS_MaxFlow(vector<vector<double>>& cap, int StartNode, int EndNode, vector<int>& parent) const {
	vector<bool> visited(SizeGraph, false);
	queue<int> q;
	q.push(StartNode);
	visited[StartNode] = true;
	parent[StartNode] = -1;

	while (!q.empty()) {
		int u = q.front();
		q.pop();

		for (int v = 0; v < SizeGraph; v++) {
			if (!visited[v] && cap[u][v] > 0) {
				if (v == EndNode) {
					parent[v] = u;
					return true;
				}
				parent[v] = u;
				visited[v] = true;
				q.push(v);

			}
		}
	}
	return false;
}

double Graph::Ford_Fulkerson(int StartNode, int EndNode) const {
	if (edges.empty()) {
		cout << endl << "The graph has no edges. It is impossible to find the maximum flow" << endl;
		return 0;
	}
	else if (!Conteins(int_to_string(StartNode)) && !Conteins(int_to_string(EndNode))) {
		cout << endl << "There are no stations with this ID in the graph. It is impossible to find the maximum flow" << endl;
		return 0;
	}

	StartNode = GetIndex(int_to_string(StartNode));
	EndNode = GetIndex(int_to_string(EndNode));

	vector<vector<double>> cap = capacity;
	vector<int> parent(SizeGraph, -1);
	double maxFlow = 0.0;

	while (BFS_MaxFlow(cap, StartNode, EndNode, parent)) {
		double pathFlow = DBL_MAX;

		for (int v = EndNode; v != StartNode; v = parent[v]) {
			int u = parent[v];
			pathFlow = min(pathFlow, cap[u][v]);
		}

		for (int v = EndNode; v != StartNode; v = parent[v]) {
			int u = parent[v];
			cap[u][v] -= pathFlow;
			cap[v][u] += pathFlow;

		}

		maxFlow += pathFlow;
	}

	return maxFlow;
}