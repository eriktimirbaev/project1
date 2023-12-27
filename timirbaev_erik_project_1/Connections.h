#pragma once
#include "Graph.h"
#include "Utilities.h"
#include <fstream>

class Connections {
public:
    std::unordered_map<std::string, Edge> edges;
    std::set<std::string> nodes;

    bool Empty();
    void Clear() { edges.clear(); }
    void Insert(Edge& edge);
    bool UncorrectNodes(std::string start, std::string terminal);
    void CreateConnection(std::string start, std::string terminal, std::string pipe_id);
    void ViewConnections();
    void DeleteConnection_ByPipeID(std::string id);
    void DeleteConnection_ByStationID(std::string id);

    friend std::ofstream& operator << (std::ofstream& file, const Connections& connections);
private:
    void ResetNodes();
};