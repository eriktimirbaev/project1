#pragma once
#include "Utilities.h"
#include "Pipe.h"
#include "Station.h"
#include "Connections.h"
#include <unordered_map>
#include <unordered_set>

class GTS
{
public:
	std::string SelectId(std::unordered_set<std::string>& group, std::string id);

	void Data(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Edit(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Delete(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Save(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Download(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	std::unordered_set<std::string> SearchStationByFilter(std::unordered_map<std::string, Station>& group);

	std::unordered_set<std::string> SearchPipeByFilter(std::unordered_map<std::string, Pipe>& group);

	std::unordered_set<std::string> GetEditNumbers(std::unordered_set<std::string> IDs);

	void CreateConnection(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void DeleteConnection(std::unordered_map<std::string, Pipe>& pipes_group);

	void TopologicalSort(std::unordered_map<std::string, Pipe>& pipes_group);

	Connections connections;

	template<typename C>
	std::string SearchId(std::unordered_map<std::string, C>& group);

	std::unordered_set<std::string> GetFreePipes(const std::unordered_set<std::string>& IDs);

	void ViewConnections();
};