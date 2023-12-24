#pragma once
#include "Utilities.h"
#include "Pipe.h"
#include "Station.h"
#include <unordered_map>
#include <unordered_set>

class GTS
{
public:
	void Data(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Edit(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Delete(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Save(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	void Download(std::unordered_map<std::string, Pipe>& pipes_group, std::unordered_map<std::string, Station>& stations_group);

	std::unordered_set<std::string> SearchStationByFilter(std::unordered_map<std::string, Station>& group);

	std::unordered_set<std::string> SearchPipeByFilter(std::unordered_map<std::string, Pipe>& group);

	std::unordered_set<std::string> GetEditNumbers(std::unordered_set<std::string> IDs);

};