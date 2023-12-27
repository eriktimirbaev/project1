#include "GTS.h"
#include <format>
#include <chrono>

using namespace std;
using namespace chrono;

void print_menu() {
	cout << "MENU" << endl
		<< "1. Add a pipe" << endl
		<< "2. Add a compressor station" << endl
		<< "3. Viewing all objects" << endl
		<< "4. Edit" << endl
		<< "5. Save all" << endl
		<< "6. Download" << endl
		<< "7. Delete" << endl
		<< "8. Graph" << endl
		<< "0. Exit" << endl
		<< "Please enter an integer from 0 to 8: ";
}

void menu() {
	GTS system;
	unordered_map<string, Pipe> pipes_group;
	unordered_map<string, Station> stations_group;

	while (true) {
		print_menu();
		switch (get_correct_number(0, 8))
		{
		case 1:
		{
			Pipe pipe;
			pipe = pipe.add_pipe(pipe);
			pipes_group.insert({ pipe.GetId(), pipe });
			break;
		}
		case 2:
		{
			Station station;
			station = station.add_station(station);
			stations_group.insert({ station.GetId(), station });
			break;
		}
		case 3: { system.Data(pipes_group, stations_group); break; }
		case 4: { system.Edit(pipes_group, stations_group); break; }
		case 5: { system.Save(pipes_group, stations_group); break; }
		case 6: { system.Download(pipes_group, stations_group); break; }
		case 7: { system.Delete(pipes_group, stations_group); break; }
		case 8:
		{
			cout << "1. Create connection" << endl
				<< "2. Delete connection" << endl
				<< "3. View connections" << endl
				<< "4. Topological sort" << endl
				<< "5. Shortest path" << endl
				<< "6. Algorithm Ford-Falkerson" << endl
				<< "0. Back" << endl
				<< "Please enter an integer from 0 to 6: ";;

			switch (get_correct_number(0, 6)) {
			case 1: { system.CreateConnection(pipes_group, stations_group); break; }
			case 2: { system.DeleteConnection(pipes_group, stations_group); break; }
			case 3: { system.ViewConnections(); break; }
			case 4: { system.TopologicalSort(pipes_group); break; }
			case 5: { system.ShortestPath(pipes_group, stations_group); break; }
			case 6: { system.MaxFlow(pipes_group, stations_group); break; }
			case 0: { break; }
			}
			break;
		}
		case 0: { exit(0); break; }
		default: { cout << "Error! Enter an integer from 0 to 8." << endl; }
		}
	}
}

int main() {
	redirect_output_wrapper cerr_out(cerr);
	string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now());
	ofstream logfile("log_" + time);
	if (logfile) cerr_out.redirect(logfile);

	menu();

	return 0;
}