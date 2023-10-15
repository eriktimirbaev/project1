#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Pipe {
	string name;
	int length;
	int diameter;
	bool repair;
};

struct Station {
	string name;
	int workshops;
	int workshops_in_operation;
	int effectiveness;
};

bool int_check(string input) {
	for (int i = 0; i < input.length(); i++) {
		if (isdigit(input[i])) continue;
		else return false;
	}
	if (input.length() == 0) return false;
	return true;
}

bool bool_check(string input) {
	if (input.length() == 1 && input[0] == '0' || input[0] == '1') return true;
	else return false;
}

string split(string str) {
	for (int i = 0; i < str.length() ; i++) {
		if (str[i] == ':') {
			str.erase(0, i + 2);
			return str;
		}
	}
}

Pipe add_pipe(Pipe& p) {
	string len, diam, rep;
	while (true) {
		cout << "Enter the name of the pipe: "; getline(cin, p.name);
		if (p.name.empty()) cout << "Error!" << endl;
		else break;
	}
	while (true) {
		cout << "Enter the length of the pipe: "; getline(cin, len);
		if (int_check(len) == true) {
			p.length = stoi(len);
			if (p.length > 0) break;
			else cout << "Error!" << endl;
		}
		else cout << "Error!" << endl;
	}
	while (true) {
		cout << "Enter the diameter of the pipe: "; getline(cin, diam);
		if (int_check(diam) == true) {
			p.diameter = stoi(diam);
			if (p.diameter > 0) break;
			else cout << "Error!" << endl;
			break;
		}
		else cout << "Error!" << endl;
	}
	while (true) {
		cout << "Pipe under repair (0; 1): "; getline(cin, rep);
		if (bool_check(rep) == true) {
			p.repair = stoi(rep);
			break;
		}
		else cout << "Error!" << endl;
	}
	return p;
}

Station add_station(Station& s) {
	string wsh, wshio, eff;
	while (true) {
		cout << "Enter the name of the compressor station: "; getline(cin, s.name);
		if (s.name.empty()) cout << "Error!" << endl;
		else break;
	}
	while (true) {
		cout << "Enter the number of the workshops: "; getline(cin, wsh);
		if (int_check(wsh) == true) {
			s.workshops = stoi(wsh);
			if (s.workshops > 0) break;
			else cout << "Error!" << endl;
		}
		else cout << "Error!" << endl;
	}
	while (true) {
		cout << "Workshops in operation: "; getline(cin, wshio);
		if (int_check(wshio) == true) {
			s.workshops_in_operation = stoi(wshio);
			if (s.workshops >= s.workshops_in_operation) break;
			else cout << "Error!" << endl;
		}
		else cout << "Error!" << endl;
	}
	while (true) {
		cout << "Effectiveness: "; getline(cin, eff);
		if (int_check(eff) == true) {
			s.effectiveness = stoi(eff);
			break;
		}
		else cout << "Error!" << endl;
	}
	return s;
}

void edit_pipe(Pipe& p) {
	if (p.name.empty()) cout << "Please add a pipe." << endl;
	else {
		while (true) {
			string rep;
			cout << "Pipe under repair (0; 1): "; getline(cin, rep);
			if (bool_check(rep) == true) {
				p.repair = stoi(rep);
				break;
			}
			else cout << "Error!" << endl;
		}
	}
}

void edit_station(Station& s) {
	if (s.name.empty()) cout << "Please add a compressor station." << endl;
	else {
		while (true) {
			string wshio;
			cout << "Workshops in operation: "; getline(cin, wshio);
			if (int_check(wshio) == true) {
				s.workshops_in_operation = stoi(wshio);
				if (s.workshops >= s.workshops_in_operation) break;
				else cout << "Error!" << endl;
			}
			else cout << "Error!" << endl;
		}
	}
}

void data(const Pipe& p, const Station& s) {
	if (p.name.empty()) cout << "Please add a pipe." << endl;
	else {
		cout << "Pipe name: " << p.name
			<< "\nPipe length: " << p.length
			<< "\nPipe diameter: " << p.diameter
			<< "\nRepair: " << p.repair << endl;
	}
	if (s.name.empty()) cout << "Please add a compressor station." << endl;
	else {
		cout << "Station name: " << s.name
			<< "\nWorkshops: " << s.workshops
			<< "\nWorkshops in operation: " << s.workshops_in_operation
			<< "\nEffectiveness: " << s.effectiveness << endl;
	}
}

void to_file(const Pipe& p, const Station& s) {
	if (p.name.empty() && s.name.empty()) cout << "Please add a pipe and a station." << endl;
	else if (!p.name.empty() && s.name.empty()) {
		ofstream file;
		file.open("data.txt", ios::out);
		if (file.is_open()) {
			file << "Pipe:" << endl
				<< p.name << endl
				<< p.length << endl
				<< p.diameter << endl
				<< p.repair << endl;
			file.close();
			cout << "Saving completed!" << endl;
		}
	}
	else if (p.name.empty() && !s.name.empty()) {
		ofstream file;
		file.open("data.txt", ios::out);
		if (file.is_open()) {
			file << "Station:" << endl
				<< s.name << endl
				<< s.workshops << endl
				<< s.workshops_in_operation << endl
				<< s.effectiveness << endl;
			file.close();
			cout << "Saving completed!" << endl;
		}
	}
	else {
		ofstream file;
		file.open("data.txt", ios::out);
		if (file.is_open()) {
			file << "Pipe:" << endl
				<< p.name << endl
				<< p.length << endl
				<< p.diameter << endl
				<< p.repair << endl << endl
				<< "Station:" << endl
				<< s.name << endl
				<< s.workshops << endl
				<< s.workshops_in_operation << endl
				<< s.effectiveness << endl;
			file.close();
			cout << "Saving completed!" << endl;
		}
	}
}

void from_file(Pipe& p, Station& s) {
	ifstream file;
	string line;
	file.open("data.txt", ios::in);
	if (file.is_open()) {
		while (getline(file, line)) {
			if (line.find("Pipe:") != string::npos) {
				if (!p.name.empty()) {
					while (true) {
						string overwrite;
						cout << "Overwrite pipe data? (yes or no)" << endl; getline(cin, overwrite);
						if (overwrite == "yes") {
							getline(file, line); p.name = line;
							getline(file, line); p.length = stoi(line);
							getline(file, line); p.diameter = stoi(line);
							getline(file, line); p.repair = stoi(line);
							break;
						}
						else if (overwrite == "no") break;
					}
				}
				else {
					getline(file, line); p.name = line;
					getline(file, line); p.length = stoi(line);
					getline(file, line); p.diameter = stoi(line);
					getline(file, line); p.repair = stoi(line);
				}
			}
			else if (line.find("Station:") != string::npos) {
				if (!s.name.empty()) {
					while (true) {
						string overwrite;
						cout << "Overwrite station data? (yes or no)" << endl; getline(cin, overwrite);
						if (overwrite == "yes") {
							getline(file, line); s.name = line;
							getline(file, line); s.workshops = stoi(line);
							getline(file, line); s.workshops_in_operation = stoi(line);
							getline(file, line); s.effectiveness = stoi(line);
							break;
						}
						else if (overwrite == "no") break;
					}
				}
				else {
					getline(file, line); s.name = line;
					getline(file, line); s.workshops = stoi(line);
					getline(file, line); s.workshops_in_operation = stoi(line);
					getline(file, line); s.effectiveness = stoi(line);
				}
			}
		}
		file.close();
		cout << "Loading completed!" << endl;
	}
	else cout << "Error! File not found!" << endl;
}

void menu() {
	Pipe pipe;
	Station station;
	string input;
	int num;
	while (true) {
		cout << "MENU" << endl
			<< "1. Add a pipe" << endl
			<< "2. Add a compressor station" << endl
			<< "3. Viewing all objects" << endl
			<< "4. Edit a pipe" << endl
			<< "5. Edit a compressor station" << endl
			<< "6. Save all" << endl
			<< "7. Download" << endl
			<< "0. Exit" << endl
			<< "Please enter an integer from 0 to 7: ";
		getline(cin, input);
		if (int_check(input) == true) {
			num = stoi(input);
			switch (num)
			{
			case 1:
				pipe = add_pipe(pipe);
				break;
			case 2:
				station = add_station(station);
				break;
			case 3:
				data(pipe, station);
				break;
			case 4:
				edit_pipe(pipe);
				break;
			case 5:
				edit_station(station);
				break;
			case 6:
				to_file(pipe, station);
				break;
			case 7:
				from_file(pipe, station);
				break;
			case 0:
				exit(0);
				break;
			default:
				cout << "Error! Enter an integer from 0 to 7." << endl;
			}
		}
		else cout << "Error! Enter an integer from 0 to 7." << endl;
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	menu();
	return 0;
}