#include "GTS.h"
#include <filesystem>

using namespace std;

template <typename C> 
string GTS::SearchId(unordered_map<string, C>& group) {
	while (true) {
		string id;
		getline(cin, id);
		if (auto i = group.find(id); i != group.end()) { return id; }
		else { std::cout << "ID not found! Please try again: "; }
	}
}

string GTS::SelectId(unordered_set<string>& group, string id) {
	if (auto i = group.find(id); i != group.end()) { return id; }
	else { std::cout << "ID not found! Please try again: "; }
}

void GTS::Data(unordered_map<string, Pipe>& pipes_group, unordered_map<string, Station>& stations_group) {
	cout << "Pipes group (0) or stations group (1): ";
	switch (get_correct_number(0, 1))
	{
	case 0:
	{
		if (pipes_group.size() != 0) {
			unordered_set<string> select_pipes = SearchPipeByFilter(pipes_group);
			for (string i : select_pipes)
				pipes_group[i].pipe_data(pipes_group[i]);
		}
		else cout << "Please add a pipe." << endl;
		break;
	}
	case 1:
	{
		if (stations_group.size() != 0) {
			unordered_set<string> select_stations = SearchStationByFilter(stations_group);
			for (string i : select_stations)
				stations_group[i].station_data(stations_group[i]);
		}
		else cout << "Please add a station." << endl;
		break;
	}
	default: { return; }
	}
}

void GTS::Edit(unordered_map<string, Pipe>& pipes_group, unordered_map<string, Station>& stations_group) {
	cout << "Pipes group (0) or stations group (1): ";
	switch (get_correct_number(0, 1))
	{
	case 0:
	{
		if (pipes_group.size() != 0) {
			unordered_set<string> select_pipes = SearchPipeByFilter(pipes_group);
			for (string i : select_pipes)
				pipes_group[i].pipe_data(pipes_group[i]);
			select_pipes = GetEditNumbers(select_pipes);
			cout << "Change the state of the pipes: set work (0), set repair (1): ";
			bool status = get_correct_number(0, 1);
			for (string i : select_pipes)
				pipes_group[i].edit_pipe(pipes_group[i], status);
		}
		else cout << "Please add a pipe." << endl;
		break;
	}
	case 1:
	{
		if (stations_group.size() != 0) {
			unordered_set<string> select_stations = SearchStationByFilter(stations_group);
			for (string i : select_stations)
				stations_group[i].station_data(stations_group[i]);
			select_stations = GetEditNumbers(select_stations);
			cout << "Change the number of the workhops in operation: ";
			int number = get_correct_number(0, 1000);
			for (string i : select_stations)
				stations_group[i].edit_station(stations_group[i], number);
		}
		else cout << "Please add a station." << endl;
		break;
	}
	default: { return; }
	}
}

void GTS::Delete(unordered_map<string, Pipe>& pipes_group, unordered_map<string, Station>& stations_group) {
	cout << "Pipes group (0) or stations group (1): ";
	switch (get_correct_number(0, 1))
	{
	case 0:
	{
		if (pipes_group.size() != 0) {
			unordered_set<string> select_pipes = SearchPipeByFilter(pipes_group);
			for (string i : select_pipes)
				pipes_group[i].pipe_data(pipes_group[i]);
			for (string i : GetEditNumbers(select_pipes))
				pipes_group.erase(i);
		}
		else cout << "Please add a pipe." << endl;
		break;
	}
	case 1:
	{
		if (stations_group.size() != 0) {
			unordered_set<string> select_stations = SearchStationByFilter(stations_group);
			for (string i : select_stations)
				stations_group[i].station_data(stations_group[i]);
			for (string i : GetEditNumbers(select_stations))
				stations_group.erase(i);
		}
		else cout << "Please add a pipe." << endl;
		break;
	}
	default: { return; }
	}
}

unordered_set<string> GTS::GetEditNumbers(unordered_set<string> IDs)
{
	unordered_set<string> res;
	cout << "Please select the Id" << endl;
	while (true) {
		string id; getline(cin, id); LOG(id);
		if (id == "0") break;
		else {
			for (string i : IDs) {
				if (i == id) {
					res.insert(i);
					break;
				}
			}
		}
	}
	return res;
}

template <typename T, typename C>
using Filter = bool(*)(C& c, T param);

template <typename C>
bool CheckByName(C& c, string param)
{
	return c.GetName().find(param) != string::npos;
}

bool CheckByRepair(Pipe& p, bool param)
{
	return p.GetRepair() == param;
}

bool CheckByPercent(Station& s, int param)
{
	return ((double)(s.GetWorkshops() - s.GetWorkshopsOperation()) / (double)s.GetWorkshops() * 100) <= param;
}

bool CheckByDiameter(Pipe& p, int param)
{
	return p.GetDiameter() == param;
}

template <typename T, typename C>
unordered_set<string> FindByFilter(unordered_map<string, C>& group, Filter<T, C> f, T param)
{
	unordered_set <string> res;
	for (auto& iter : group)
	{
		if (f(iter.second, param)) res.insert(iter.first);
	}

	return res;
}

unordered_set<string> GTS::SearchPipeByFilter(unordered_map<string, Pipe>& group) {
	cout << "Search pipes by name (0) or repair (1): ";
	switch (get_correct_number(0, 1))
	{
	case 0:
	{
		string name;
		while (true) {
			cout << "Enter the name of the pipe: "; getline(cin, name); LOG(name);
			if (name.empty()) cout << "Error!" << endl;
			else break;
		}
		return FindByFilter(group, CheckByName<Pipe>, name);
	}
	case 1:
	{
		cout << "Pipe under repair (0; 1): ";
		bool repair = get_correct_number(0, 1);
		return FindByFilter(group, CheckByRepair, repair);
	}
	}
}

unordered_set<string> GTS::SearchStationByFilter(unordered_map<string, Station>& group) {
	cout << "Search by name (0) or workshops (1): ";
	switch (get_correct_number(0, 1))
	{
	case 0:
	{
		string name;
		while (true) {
			cout << "Enter the name of the station: "; getline(cin, name); LOG(name);
			if (name.empty()) cout << "Error!" << endl;
			else break;
		}
		return FindByFilter(group, CheckByName<Station>, name);
	}
	case 1:
	{
		cout << "Please enter the percentage: ";
		int percent = get_correct_number(0, 100);
		return FindByFilter(group, CheckByPercent, percent);
	}
	}
}

void GTS::Save(unordered_map<string, Pipe>& pipes_group, unordered_map<string, Station>& stations_group)
{
	if (pipes_group.size() != 0 || stations_group.size() != 0) {
		cout << "Write name of the file to save: " << endl;
		string name; getline(cin, name); LOG(name);

		ofstream file;
		file.open(name, ios::out);
		file << pipes_group.size() << " " << stations_group.size() << endl;
		for (auto& pipe : pipes_group) { file << pipe.second; }
		for (auto& station : stations_group) { file << station.second; };
		file.close();
		cout << "Successful save!" << endl;
	}
	else { cout << "No objects to save!" << endl; }
}

void GTS::Download(unordered_map<string, Pipe>& pipes_group, unordered_map<string, Station>& stations_group) {
	ifstream file;
	std::string path = "C:/Users/User/Documents/GitHub/project1/timirbaev_erik_project_1";
	vector<std::filesystem::directory_entry> names;
	int count = 0;
	for (auto& name : filesystem::directory_iterator(path)) {
		if (name.path().extension() == ".txt") {
			count++;
			names.push_back(name);
			cout << count << ". " << name.path().filename() << endl;
		}
	}
	cout << "Choose the file: ";
	int download = get_correct_number(1, count);

	pipes_group.clear();
	stations_group.clear();
	Pipe pipe;
	Station station;
	int count_pipes, count_stations;

	file.open(names[download - 1]);
	file >> count_pipes >> count_stations;

	while (count_pipes--)
	{
		file >> pipe;
		pipes_group.insert({ pipe.GetId(), pipe });
	}
	while (count_stations--)
	{
		file >> station;
		stations_group.insert({ station.GetId(), station });
	}
	cout << "Successful download!" << endl;
	file.close();
}

void GTS::ViewConnections() {
	connections.ViewConnections();
}

unordered_set<string> GTS::GetFreePipes(const unordered_set<string>& IDs) {
	unordered_set<string> free_IDs;
	for (auto& id : IDs) {
		if (!connections.edges.contains(id)) {
			free_IDs.insert(id);
		}
	}
	return free_IDs;
}

void GTS::CreateConnection(unordered_map<string, Pipe>& pipes_group, unordered_map<string, Station>& stations_group) {
	if (stations_group.size() < 2) { cout << "There are not enough stations to create a connection!" << endl; return; }
	for (auto& station : stations_group) station.second.station_data(station.second);
	string start_station, terminal_station, pipe_id;
	cout << "Enter the ID of the starting station: ";
	start_station = SearchId(stations_group);
	cout << "Enter the ID of the terminal station: ";
	terminal_station = SearchId(stations_group);

	if (connections.UncorrectNodes(start_station, terminal_station)) { return; }
	cout << "Diameters of the pipes:" << endl << "1. 500" << endl << "2. 700" << endl << "3. 1000" << endl << "4. 1400" << endl
		<< "Enter the diameter of the pipe (millimeters): ";
	int diameter = get_correct_number(0, 1400);
	unordered_set<string> select_pipes = FindByFilter(pipes_group, CheckByDiameter, diameter);
	for (string i : select_pipes)
		pipes_group[i].pipe_data(pipes_group[i]);
	cout << "Enter the ID of the pipe: ";
	pipe_id = SelectId(select_pipes, SearchId(pipes_group));
	select_pipes = GetFreePipes({ pipe_id });

	if (select_pipes.size() == 0) {
		cout << "The pipes have not been found or they are already in connection.\nDo you want to create such a pipe?\nNo(0), Yes(1): ";
		if (!get_correct_number(0, 1)) { return; }
		else {
			Pipe pipe;
			pipe.add_pipe_with_diameter(pipe, diameter);
			pipe_id = pipe.GetId();
			pipes_group.insert({ pipe_id, pipe });
			connections.CreateConnection(start_station, terminal_station, pipe_id);
			return;
		}
	}
	else {
		connections.CreateConnection(start_station, terminal_station, pipe_id);
		return;
	}
}

void GTS::DeleteConnection(unordered_map<string, Pipe>& pipes_group) {
	if (connections.Empty()) {
		cout << "No connections available!" << endl;
		return;
	}

	connections.ViewConnections();
	cout << "Enter the ID of the connection to be deleted: ";
	string id;
	do {
		id = SearchId(pipes_group);
		if (!connections.edges.contains(id)) { cout << "There is no such ID among the pipes found! Enter it again." << endl; }
	} while (!connections.edges.contains(id));
	connections.DeleteConnection_ByPipeID(id);
}

void GTS::TopologicalSort(unordered_map<string, Pipe>& pipes_group) {
	if (connections.Empty()) { cout << "No connections available!"; return; }
	Graph graph = Graph(connections.edges, connections.nodes, pipes_group);
	vector<string> result = graph.TopologicalSort();
	if (!result.size()) { cout << "Topological sort: - "; return; }
	cout << "Topological sorting: ";
	for (auto& i : result) {
		cout << i << " ";
	}
	cout << endl;
}