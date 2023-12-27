#include "Connections.h"


using namespace std;

bool Connections::Empty()
{
    if (edges.size()) { return false; }
    else { return true; }
}

void Connections::Insert(Edge& edge) {
    edges.insert({ edge.pipe_id, edge });
    nodes.insert({ edge.start });
    nodes.insert({ edge.terminal });
}

bool Connections::UncorrectNodes(string start, string terminal)
{
    if (start == terminal) {
        cout << "It is impossible to establish a connection to the same station!" << endl; return true;
    }
    else { return false; }
}

void Connections::CreateConnection(string start, string terminal, string pipe_id) {
    if (UncorrectNodes(start, terminal)) { return; }
    if (edges.contains(pipe_id)) {
        cout << "The stations or the pipe are already involved!" << endl; return;
    }
    Edge edge = Edge(start, terminal, pipe_id);
    edges.insert({ pipe_id, edge });
    nodes.insert(start);
    nodes.insert(terminal);
    cout << "The connection created!" << endl;
    return;
}

void Connections::ViewConnections()
{
    if (edges.empty()) { cout << "There are no connections!" << endl; }
    for (auto& edge : edges) {
        cout << "Connection: pipe " << edge.second.pipe_id << " connects stations "
            << edge.second.start << " -> " << edge.second.terminal << endl;
    }
}

void Connections::DeleteConnection_ByPipeID(string pipe_id) {
    if (edges.contains(pipe_id)) {
        edges.erase(pipe_id);
        cout << "Connection " << pipe_id << " deleted" << endl;
        ResetNodes();
    }
}

void Connections::DeleteConnection_ByStationID(string station_id) {
    vector<string> ID_edges;
    for (auto& [pipe_id, edge] : edges) {
        if (edge.start == station_id || edge.terminal == station_id) { ID_edges.push_back(pipe_id); }
    }

    for (string id : ID_edges) {
        edges.erase(id);
        cout << "Connection " << id << " deleted" << endl;
    }
    ResetNodes();
}

void Connections::ResetNodes()
{
    nodes.clear();
    for (auto& edge : edges) {
        nodes.insert(edge.second.start);
        nodes.insert(edge.second.terminal);
    }
}

ofstream& operator << (ofstream& file, const Connections& connections) {
    if (file.is_open()) {
        for (auto& edge : connections.edges) { file << edge.second; }
    }
    return file;
}